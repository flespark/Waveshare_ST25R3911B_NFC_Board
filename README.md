### WaveShare ST25R3911B NFC Board DEMO

基于vscode的[微雪 ST25R3911B NFC Board](https://www.waveshare.net/wiki/ST25R3911B_NFC_Board)开发环境，cmake作为构建工具，gcc作为编译器，jlink作为烧录调试工具，clangd作为代码索引和lint工具, ccache用于加快编译速度

#### 如何使用

1. 首先在系统上安装必需的开发工具，开源软件在Windows下建议使用[scoop](https://scoop.sh/#/)安装：

```
scoop install vscode cmake ninja gcc-arm-none-eabi clangd ccache
```

    Linux可能需要额外安装`arm-none-eabi-newlib`软件包

2. 安装jlink，使用厂商提供中的资料 [FAQ0132_JLink手动添加Artery MCU_V2.0.0.zip](https://www.arterytek.com/file/download/375)，根据其中的说明文档修改jlink以添加对AT32支持
3. 打开vscode打开工程目录，安装推荐的插件
4. 调试器接到AT32F413的SWD调试接口，vscode下方状态栏中的Build[F4]，Flash[F6]，Reset[F7]，Erase[F8]对应编译，烧录，复位，擦除操作， 调试[F5]借助[cortex-debug](https://github.com/Marus/cortex-debug/wiki)插件。配置相应的快捷键，需要添加 `.vscode/keybindings.json`中的相关配置项到vscode的系统快捷键配置文件中

#### 注意

- 淘宝购买的发货版本可能将MCU替换为了AT23F413RC, 此工程仅适用于STM32F103RC版本, 所以MCU需要换回来
- 修改 cmake/launch.json.in 中的 `serialNumber` 为实际jlink的序列号，`armToolchainPath` 为gcc-arm-none-eabi的实际安装路径，`Ctrl+Shift+P` 打开vscode command palette 重新执行 `cmake generate`
- Windows若报编译错误，执行cmake配置生成时显式指定编译器为Ninja