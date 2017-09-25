{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "desktop-screenshot",
      "sources": [ "addon/raw-desktop-screenshot.cpp" ],
      'conditions': [
        ['OS == "mac"', {
          'include_dirs': [
            'System/Library/Frameworks/ApplicationServices.framework/Headers'
          ],
          'link_settings': {
            'libraries': [
              '-framework ApplicationServices'
            ]
          }
        }]
      ]      
    }
  ]
}