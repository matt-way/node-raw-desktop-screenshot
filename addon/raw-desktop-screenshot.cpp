#include <nan.h>
#include <ApplicationServices/ApplicationServices.h>

class CaptureWorker : public Nan::AsyncWorker {
public:
  CaptureWorker(Nan::Callback *cb) : Nan::AsyncWorker(cb) {}
  ~CaptureWorker() {}

  void Execute() {
    // get screen image and put the data into a ref
    image = CGDisplayCreateImage(kCGDirectMainDisplay); 
    rawData = CGDataProviderCopyData(CGImageGetDataProvider(image));

    // calculate sizes
    width = CGImageGetWidth(image);
    height = CGImageGetHeight(image);

    // get access to the pixel memory
    rawBuffer = CFDataGetBytePtr(rawData);
    length = CFDataGetLength(rawData);
  }

  void HandleOKCallback () {
    Nan::HandleScope scope;

    // create an array buffer for the image
    v8::Handle<v8::ArrayBuffer> imageBuffer = v8::ArrayBuffer::New(v8::Isolate::GetCurrent(), length);
    memcpy(imageBuffer->GetContents().Data(), rawBuffer, length);

    // build return object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    obj->Set(Nan::New("width").ToLocalChecked(), Nan::New(width));
    obj->Set(Nan::New("height").ToLocalChecked(), Nan::New(height));
    obj->Set(Nan::New("image").ToLocalChecked(), imageBuffer);

    v8::Local<v8::Value> argv[] = {
      Nan::Null(),
      obj
    };

    callback->Call(2, argv);

    // osx image cleanup
    CFRelease(rawData);
    CGImageRelease(image);
  }

private:
  CGImageRef image;
  CFDataRef rawData;
  int width;
  int height;
  const UInt8* rawBuffer;
  CFIndex length;
};

NAN_METHOD(capture) {
  Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[0]).ToLocalChecked());
  Nan::AsyncQueueWorker(new CaptureWorker(callback));
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, capture);
}

NODE_MODULE(desktopScreenshot, Initialize);

