{
    "targets": [
        {
            "target_name": "ChiikaNative",
            "cflags_cc": [ "-std=c++11" ],
            "sources": [
                    "src/Init.cc",
                    "src/ApiWrapper.h",
                    "src/ApiWrapper.cc"
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
                    "deps/curl/x64/Release/libcurl_imp.lib",
                    "deps/curl/x64/Release/libcurl.dll",
                    "deps/jsoncpp/x64/Release/jsoncpp.lib",
                    "deps/jsoncpp/x64/Release/jsoncpp.dll",
                    "deps/pugixml/x64/Release/pugixml.lib",
                    "deps/pugixml/x64/Release/pugixml.dll",
                    "deps/Chiika/x64/Release/ChiikaApi.lib",
                    "deps/Chiika/x64/Release/ChiikaApi.dll"
                ]
            }],
            "configurations": {
                "Debug": {
                    "msvs_settings": {
                        "VCCLCompilerTool": {
                            "ExceptionHandling": "0",
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
                                "<(CURRENT_DIR)/deps/curl/x64/Debug",
                                "<(CURRENT_DIR)/deps/jsoncpp/x64/Debug",
                                "<(CURRENT_DIR)/deps/pugixml/x64/Debug",
                                "<(CURRENT_DIR)/deps/Chiika/x64/Debug"
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
                                                            "$(SolutionDir)/../deps/curl/x64/Release",
                                                            "$(SolutionDir)/../deps/jsoncpp/x64/Release",
                                                            "$(SolutionDir)/../deps/pugixml/x64/Release",
                                                            "$(SolutionDir)/../deps/Chiika/x64/Release"
                             ]
                        }
                    }
                }
            },
            "include_dirs": [
                "<!(node -e \"require('nan')\")",
                "D:\Chiika\ChiikaApiGit\ChiikaApi\ChiikaAPI"
            ]
        }
    ]
}
