# SDLShooter
C++游戏开发的入门教程，利用SDL2（SDL3）开发一款太空战机类型的游戏

## 项目简介
此项目为教学演示用途，配套教程：[视频](https://www.bilibili.com/video/BV1wSCFYQEyc/?share_source=copy_web&vd_source=38785218fa1d2c5dfde79f8b24baf0b6)，[文字](https://cppgamedev.top/courses/sdl-space-shooter)

提示：仓库中包含了所有课节的代码，你可以根据视频教程的进度查找对应的代码。<img src="https://theorhythm.top/gamedev/tags.png" style='width: 400px;' />
<img src="https://theorhythm.top/gamedev/download.png" style='width: 800px;' />

或者使用Git更加方便地查看代码，参考此教程：[利用Git快速查看课节代码](https://www.bilibili.com/video/BV1H7KGerEAa/)

本项目为CC0 1.0许可，这意味着你可以随意使用此代码且无需署名，但如果你给出Github链接或者视频教程的链接，我会非常感激。

## 游戏截图

<div style="display: flex; gap: 10px;">
  <img src="https://theorhythm.top/gamedev/screen_shooter_1.png" width="300" />
  <img src="https://theorhythm.top/gamedev/screen_shooter_2.png" width="300" />
</div>
<div style="display: flex; gap: 10px;">
  <img src="https://theorhythm.top/gamedev/screen_shooter_3.png" width="300" />
  <img src="https://theorhythm.top/gamedev/screen_shooter_4.png" width="300" />
</div>

## 环境配置
请根据你自己的平台（Linux、MacOS、Windows）参考各自的配置方法。
<img src="https://theorhythm.top/gamedev/e0e61e011a78289052592632c1361636.png" />
## Ubuntu Linux
1. 安装cmake和SDL相关库。打开终端，输入：
```bash
sudo apt install cmake libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```
至此即完成配置。

### MacOS
1. 测试你的电脑是否安装了homebrew。终端输入：
	```bash
	brew --version
	```
	显示 `Homebrew (版本号)` 即表示已经安装，可以跳过第2步。否则需要进行第2步安装。
2. 安装brew：[官网](https://brew.sh/)、[国内安装方法](https://www.cnblogs.com/Wcowin/p/17062207.html)。安装完成后可重复第1步以测试是否安装成功。
3. 安装命令行工具。在终端内输入：
	```
	xcode-select --install
	```
	按照提示安装即可。如果显示 `... Command line tools are already installed. ...` 则表示之前已经安装了，可以继续往下执行。
4. 通过homebrew安装cmake和SDL相关库。终端输入：
	```bash
	brew install cmake sdl2 sdl2_image sdl2_mixer sdl2_ttf
	```
	提示安装完毕后即可完成配置。

### Windows
1. 安装Visual Studio 生成工具。首先打开[官网](https://visualstudio.microsoft.com/zh-hans/downloads/)，下拉网页找到“用于Visual Studio的工具”。展开后找到“Visual Studio 2022 生成工具”下载安装。<img src="https://theorhythm.top/gamedev/7ff398f915dbedd2b382451a7c5cb184.png" style='width: 800px;' /><img src="https://theorhythm.top/gamedev/116473927cc188862aaad4df9be93761.png" style='width: 800px;' />
<img src="https://theorhythm.top/gamedev/463dd4c2280d54b6f1ac16634653b4de.png" style='width: 800px;' />

2. 分别下载[sdl2](https://github.com/libsdl-org/SDL/releases/)，[SDL2-image](https://github.com/libsdl-org/SDL_image/releases), [SDL2-mixer](https://github.com/libsdl-org/SDL_mixer/releases), [sdl2-ttf](https://github.com/libsdl-org/SDL_ttf/releases) 的msvc开发版。<img src="https://theorhythm.top/gamedev/1dd680c2fdcfecbdb45534d6d5f78501.png" style='width: 800px;' /> 下载后将4个文件全部解压到任意指定文件夹中（例如 `C:\Library\SDL2`）。<img src="https://theorhythm.top/gamedev/bfbeb9fe00f29d39aea12306c0cf69c8.png" style='width: 800px;' />
> 如果因为网络因素下载困难，也可以直接使用我下载好的SDL库：[百度网盘](https://pan.baidu.com/s/1aGyLFfrQQlOylKy03WLL-g?pwd=hmjz)，版本与教程相同

3. 设置环境变量，将上一步得到的`文件夹路径` 及 `文件夹路径\lib\x64` 添加到Path变量中<img src="https://theorhythm.top/gamedev/03c93aa96af29d93c4889cc10c14a123.png" />

### 安装并配置Visual Studio Code编辑器
这一节所有平台都一样。
1. 打开[官网](https://code.visualstudio.com/)，选择对应平台的安装包下载安装<img src="https://theorhythm.top/gamedev/f5a290cbf12c10e0feedd119034e5925.png" style='width: 800px;' />

2. 在插件页面搜索“C++”，然后安装插件：`C/C++ Extension Pack` <img src="https://theorhythm.top/gamedev/a6aa4619a9095f51649b4393cc7afd8c.png" style='width: 800px;' /> 至此配置已经完成，后面几步可任选是否执行。

3. 可选：再次搜索Chinese，安装插件 `Chinese (Simplified) (简体中文)` ，重启后即可改成中文界面。

4. 可选：打开“设置”并搜索“cmake status bar”，将“Status Bar Visibility” 改为“visible”。（此设置可方便地更改编译模式为debug或者release等）。<img src="https://theorhythm.top/gamedev/aace361efb69b6c08ab5b783a27887af.png" style='width: 800px;' />

5. 可选：搜索安装AI辅助插件（选一个安装即可，以免冲突）。
	- 如果无法科学上网，推荐国内可用且下载量大的，例如 `CodeGeeX`，`fitten`等。
	- 如果能够科学上网，免费的推荐`Codeium`，付费的推荐 `Github Copilot`。

## 素材包下载
百度网盘：https://pan.baidu.com/s/1sTj6cp49sxvMWmfWGhvmgw?pwd=2bk8

## 致谢
游戏素材来自于以下作者，均为CC0 1.0许可/无要求（你可以随意使用而无需署名），感谢他们的贡献：
- 图片素材：
  - https://anim86.itch.io/space-shoter-starter-pack
  - https://doshrosity.itch.io/32x32-health-ui
- 音效素材
  - https://enprimer.itch.io/spaceship-sound-effects-pack
- 音乐素材
  - https://leohpaz.itch.io/space-music-pack
- 字体素材
  - https://timothyqiu.itch.io/vonwaon-bitmap
- 爆炸特效
  - https://ansimuz.itch.io/explosion-animations-pack