{
'conditions': [
  ['OS=="linux"', {

  }],
  ['OS=="win"', {
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
            "copies":[{
                'destination': '<(PRODUCT_DIR)',
                "files":[
                        "../ChiikaApi/build/Chiika/Debug/ChiikaApi.lib",
                        "../ChiikaApi/build/Chiika/Debug/ChiikaApi.dll",
                        "../ChiikaApi/build/Chiika/Debug/libcurl_imp.lib",
                        "../ChiikaApi/build/Chiika/Debug/libcurl.dll"
                ]
            }],
            "link_settings": {
                "libraries": [
                    "-llibcurl_imp",
                    "-lChiikaApi"
                ]
            },
            "variables":{
                "CURRENT_DIR":"<!(echo %~dp0)"
            },
            "configurations": {
                "Debug": {
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
                                "../../ChiikaApi/build/Chiika/Debug",
                             ]
                        }
                    }
                },
                "Release": {
                    "msvs_settings": {
                        "VCCLCompilerTool": {
                            "ExceptionHandling": "0",
                            "AdditionalOptions": [
                                "/MT"
                            ]
                        }
                    }
                }
            },
            "include_dirs": [
                "<!(node -e \"require('nan')\")",
                "../ChiikaApi/ChiikaAPI"
            ]
        }
    ]}
]]
}
