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
            "link_settings": {
                "libraries": [
                    "-llibcurl_imp",
                    "-ljsoncpp",
                    "-lChiikaApi",
                    "-lpugixml"
                ]
            },
            "variables":{
                "CURRENT_DIR":"<!(echo %~dp0)"
            },
            "copies":[{
                'destination': '<(PRODUCT_DIR)',
                "files":[
                                        "deps/x86_64/Debug/libcurl_imp.lib",
                                        "deps/x86_64/Debug/libcurl.dll",
                                        "deps/x86_64/Debug/jsoncpp.lib",
                                        "deps/x86_64/Debug/jsoncpp.dll",
                                        "deps/x86_64/Debug/pugixml.lib",
                                        "deps/x86_64/Debug/pugixml.dll",
                                        "deps/x86_64/Debug/ChiikaApi.lib",
                                        "deps/x86_64/Debug/ChiikaApi.dll"
                ]
            }],
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
                                "$(SolutionDir)/../deps/x86_64/Debug",
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
                        },
                        "VCLibrarianTool": {
                        },
                        "VCLinkerTool": {
                            "AdditionalLibraryDirectories": [
                                                            "$(SolutionDir)/../deps/x86_64/Release"
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
    ]
}
