{
   "variables": {
  	  "chiikaapi_output%": "/home/arkenthera/code/chiika-node/ChiikaApi/build/Chiika"
    },
    "targets": [
        {
            "target_name": "ChiikaNative",
            "cflags_cc": [ "-std=c++11" ],
            "sources": [
                    "src/Common.h",
                    "src/Init.cc",
                    "src/ApiWrapper.h",
                    "src/ApiWrapper.cc",
					"src/RequestWrapper.h",
					"src/RequestWrapper.cc",
                    "src/DatabaseWrapper.h",
                    "src/DatabaseWrapper.cc",
                    "src/Converters.cc",
                    "src/Converters.h"
            ],
            "cflags": [
                "-std=c++11"
            ],
            "defines!":[
                '_HAS_EXPECTIONS=0'
            ],
            'conditions': [
                ['OS=="mac"', {
                  'xcode_settings': {
                        'MACOSX_DEPLOYMENT_TARGET': '10.8',
                        'OTHER_CPLUSPLUSFLAGS' : ['-stdlib=libc++'],
                    },
                    "ldflags":[
                        "-Wl,-rpath,<!(pwd)/ChiikaApi/build/Chiika/"
                    ],
                    "libraries":[
                        "<!(pwd)/ChiikaApi/build/Chiika/libChiikaApi.dylib"
                    ],
                    "copies": [{
                        'destination': '<(PRODUCT_DIR)',
                        "files":[
                                "ChiikaApi/build/Chiika/libChiikaApi.dylib",
                                "ChiikaApi/build/Chiika/libcurl.dylib"
                        ]
                    }],
                },
                'OS=="linux"', {
                    "ldflags":[
                        "-Wl,-rpath,<!(pwd)/ChiikaApi/build/Chiika/"
                    ],
                    "libraries":[
                        "<!(pwd)/ChiikaApi/build/Chiika/libChiikaApi.so"
                    ],
                    "copies": [{
                        'destination': '<(PRODUCT_DIR)',
                        "files":[
                                "ChiikaApi/build/Chiika/libChiikaApi.so",
                                "ChiikaApi/build/Chiika/libcurl.so"
                        ]
                    }],
                },
                "OS=='win'",{
                    "copies": [{
                        'destination': '<(PRODUCT_DIR)',
                        "files":[
                            "ChiikaApi/build/Chiika/Debug/ChiikaApi.lib",
                            "ChiikaApi/build/Chiika/Debug/ChiikaApi.dll",
                            "ChiikaApi/build/Chiika/Debug/libcurl_imp.lib",
                            "ChiikaApi/build/Chiika/Debug/libcurl.dll"
                        ]
                    }],
                    "configurations":{
                        "Debug":{
                            "msvs_settings": {
                                "VCCLCompilerTool": {
                                    "ExceptionHandling": "1",
                                    "AdditionalOptions": [
                                        "/MTd"
                                    ]
                                },
                                "VCLibrarianTool": {
                                },
                                "VCLinkerTool": {
                                    "LinkTimeCodeGeneration": 1,
                                    "LinkIncremental": 1,
                                    "AdditionalLibraryDirectories": [
                                        "<(PRODUCT_DIR)/../../ChiikaApi/build/Chiika/Debug",
                                     ]
                                }
                            },
                        }
                    }
                }]
            ],
            "variables":{
                "CURRENT_DIR":"<!(echo %~dp0)"
            },
            "include_dirs": [
                "<!(node -e \"require('nan')\")",
                "ChiikaApi/ChiikaAPI"
            ]
        }
    ]
}
