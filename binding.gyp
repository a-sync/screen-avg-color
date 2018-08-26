{
    "targets": [
        {
            "target_name": "screen_avg_color",
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ],
            "conditions": [
#                ['OS=="linux"', {
#                    "sources": ["src/linux/screen_avg_color_linux_addon.cpp", "src/linux/screen_avg_color_linux.c"],
#                    "link_settings": {
#                        "libraries": [
#                            "-lX11",
#                            "-lpng"
#                        ]
#                    }
#                }],
#                ['OS=="mac"', {
#                    'xcode_settings': {
#                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
#                        'OTHER_CFLAGS': [
#                            '-ObjC++'
#                        ]
#                    },
#                    "sources": ["src/osx/screen_avg_color_osx_addon.cpp", "src/osx/screen_avg_color_osx.mm"],
#                    "link_settings": {
#                        "libraries": [
#                            "-framework CoreGraphics",
#                            "-framework CoreServices",
#                            "-framework ImageIO",
#                            "-framework Foundation"
#                        ]
#                    }
#                }],
                ['OS=="win"', {
                    "sources": ["src/windows/screen_avg_color_windows_addon.cpp", "src/windows/screen_avg_color_windows.cpp"]
                }]
            ]
        }
    ]
}
