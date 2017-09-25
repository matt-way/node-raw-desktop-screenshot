#include <nan.h>
#include <ApplicationServices/ApplicationServices.h>

NAN_METHOD(capture) {
  // get screen image and put the data into a ref
  CGImageRef image = CGDisplayCreateImage(kCGDirectMainDisplay); 
  CFDataRef rawData = CGDataProviderCopyData(CGImageGetDataProvider(image));

  // calculate sizes
  int width = CGImageGetWidth(image);
  int height = CGImageGetHeight(image);

  // get access to the pixel memory
  const UInt8* buf = CFDataGetBytePtr(rawData);
  CFIndex length = CFDataGetLength(rawData);

  // create an array buffer for the image
  v8::Handle<v8::ArrayBuffer> imageBuffer = v8::ArrayBuffer::New(v8::Isolate::GetCurrent(), length);
  memcpy(imageBuffer->GetContents().Data(), buf, length);
  
  // build return object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  obj->Set(Nan::New("width").ToLocalChecked(), Nan::New(width));
  obj->Set(Nan::New("height").ToLocalChecked(), Nan::New(height));
  obj->Set(Nan::New("image").ToLocalChecked(), imageBuffer);

  info.GetReturnValue().Set(obj);

  // osx image cleanup
  CFRelease(rawData);
  CGImageRelease(image);
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, capture);
}

NODE_MODULE(desktopScreenshot, Initialize);

