# NS3-install
## ns3.27
https://blog.csdn.net/yangzhenyu2/article/details/116205406  
### 可视化
https://blog.csdn.net/a6333230/article/details/108296948  

# NS3 + VSCODE 
## VSCODE version = 1.65
配置文字教程：https://www.bilibili.com/read/cv9932411  
配置视频教程：https://www.bilibili.com/video/BV1pU4y1W74Z/

# root权限下无法打开code
解决方法：  
cd ns3.27  
sudo chmod -R 777 build

# js文件配置
## tasks.json
···
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
···
