# 1、NS3-install
## ns3.27
### 安装教程
https://blog.csdn.net/yangzhenyu2/article/details/116205406  
### 可视化教程
https://blog.csdn.net/a6333230/article/details/108296948  

# 2、NS3 + VSCODE 
## VSCODE version = 1.65
[vscode 1.65](https://code.visualstudio.com/updates/v1_65)  
配置文字教程：https://www.bilibili.com/read/cv9932411  
配置视频教程：https://www.bilibili.com/video/BV1pU4y1W74Z/

# 3、root权限下无法打开code
代替方案：
```
cd ns3.27
sudo chmod -R 777 build
```
终端使用```code .```命令打开

# 4、js文件配置
## tasks.json
```
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "cppbuild",
			"label": "C/C++: cpp build active file",
			"command": "./waf",
			"args": [
				//"-fdiagnostics-color=always",
				//"-g",
				//"${file}",
				//"-o",
				//"${fileDirname}/${fileBasenameNoExtension}"
			],
			"options": {
				"cwd": "${workspaceFolder}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "编译器: /usr/bin/cpp"
		}
	]
}
```
## launch.json
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "waf - Build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/scratch/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "preLaunchTask": "C/C++: cpp build active file",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "miDebuggerPath": "/usr/bin/gdb"
        }

    ]
}
```
## c_cpp_proerties.json
```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/build/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c11",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```
