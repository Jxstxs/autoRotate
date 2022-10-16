
<h1 align="center">autoRotate</h1>
<p align="center">
  <img alt="GitHub" src="https://img.shields.io/github/license/Jxstxs/autoRotate?style=flat-square">
  <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/Jxstxs/autoRotate?style=flat-square">
  <img alt="GitHub issues" src="https://img.shields.io/github/issues/Jxstxs/autoRotate?style=flat-square">
</p>

C program to rotate the screen automatically based on the internal accelerator.

## Configuration

To Configure autoRotate you have to edit [config.h](./config.h) and recompile.

## Installation

Install autoRotate by running make

```bash
  sudo make install clean
```

> NOTE: only tested on Arch Linux with Xorg
    
## Features

- Automatically Rotate the Screen based on the internal Accelerator

### Todos

- Rotate Touch Devices (Stylus, Touch, ...)
- better range check Values

## Usage/Examples

- To run it in the Background type `autoRotate &`
- To enable Output `autoRotate -v`
- To show the installed Version `autoRotate -V`
- To show the Help Page `autoRotate -h`

## Contributing

Contributions are always welcome! But remember to be Kind
