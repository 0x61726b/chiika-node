{
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
            "conditions":[
                [
                    'OS=="mac"',{
                        "configurations":{
                            "Debug":{
                                "copies": [{
                                    'destination': '<(PRODUCT_DIR)',
                                    "files":[
                                            "ChiikaApi/build/Chiika/Debug/ChiikaApi.so",
                                            "ChiikaApi/build/Chiika/Debug/libcurl.so"
                                    ]
                                }],
                            }
                        }
                    },
                    "OS=='win'",{
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
                                            "D:/Arken/C++/ElectronProjects/chiika-node/ChiikaApi/build/Chiika/Debug",
                                         ]
                                    }
                                },
                                "copies": [{
                                    'destination': '<(PRODUCT_DIR)',
                                    "files":[
                                        "ChiikaApi/build/Chiika/Debug/ChiikaApi.lib",
                                        "ChiikaApi/build/Chiika/Debug/ChiikaApi.dll",
                                        "ChiikaApi/build/Chiika/Debug/libcurl_imp.lib",
                                        "ChiikaApi/build/Chiika/Debug/libcurl.dll"
                                    ]
                                }],
                            }
                        }
                    }
                ]
            ],
            "link_settings": {
                "libraries": [
                    "-llibcurl_imp",
                    "-lChiikaApi"
                ]
            },
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
