# Build your Rust-game on Termlib

## Installation
You need to have [rustc and cargo](https://rust-lang.org/learn/get-started/) and SDL2-dev packages installed

### SDL2-dev for Windows
Download [this archive](https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/SDL2-devel-2.32.10-VC.zip) for the Visual Studio compiler (used by default), or [this one](https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/SDL2-devel-2.32.10-mingw.zip) for MinGW

After that, create a `devlibs` folder on your `C:` drive, then create an `SDL2` folder inside it   
Unpack the archive and move the `include` and `lib` folders into `C:/devlibs/SDL2/`

### SDL2-dev for Linux 
Debian-based:
```bash
sudo apt update
sudo apt install libsdl2-dev
```
RHEL-based:
```bash
sudo dnf check-update
sudo dnf install SDL2-devel
```
Arch-based:
```bash
sudo pacman -Sy
sudo pacman -S sdl2
```

### SDL2-dev for MacOs
```bash
sudo port selfupdate
sudo port install libsdl2
```

## Setting up your environment 
At the end of this guide, your project structure must be:
```bash
├── Cargo.lock
├── Cargo.toml
├── build.rs
├── native
│   ├── core.c
│   └── core.h
└── src
    ├── bindings.rs
    └── main.rs
```

### 1 Step
Firstly, just create a new project:
```bash
cargo new awesome_game
```

### 2 Step
Edit your `Cargo.toml`:
```toml
[package]
name = "awesome_game"
version = "0.1.0"
edition = "2024"

[dependencies]

[build-dependencies]
cc = "1.2.45"
bindgen = "0.72.1"
```

### 3 Step
Create `native` folder and paste [`core.h`](https://github.com/Ztry8/Termlib/blob/main/src/core.h) there,   
Create `core.c` inside `native` folder and paste in it this content:
```c
#include "core.h"
```
(Yes, only one line of code in this file)

### 4 Step
Create `build.rs` in your project root and paste this code: 
```rust
fn main() {
    let path_include = "see below";
    let path_lib = "see below";

    cc::Build::new()
        .file("native/core.c")
        .include("native")
        .include(path_include)
        //.define("SHOW_FPS", None)
        .flag_if_supported("-w")
        .compile("core");

    println!("cargo:rustc-link-search=native={}", path_lib);
    println!("cargo:rustc-link-lib=SDL2");

    let bindings = bindgen::Builder::default()
        .header("native/core.h")
        .clang_arg(format!("-I{}", path_include)) 
        .clang_arg("-Inative")                        
        .generate()
        .expect("Unable to generate bindings");

    bindings
        .write_to_file("src/bindings.rs")
        .expect("Couldn't write bindings!");

    let mut content = std::fs::read_to_string("src/bindings.rs").unwrap();
    content = format!("#![allow(warnings)]\n{}", content);
    std::fs::write("src/bindings.rs", content).unwrap();
}
```
**Make sure to set up your library path!**   
There are default path for library:

#### Windows
(If you followed [the instructions](https://github.com/Ztry8/Termlib/blob/main/RustBuilding.md#sdl2-dev-for-windows) above)
```rust
let path_include = "C:/devlibs/";
let path_lib = "C:/devlibs/";
```

#### Linux
```rust
let path_include = "/usr/include/";
let path_lib = "/usr/lib";
// let path_lib = "/usr/lib64";
```

#### MacOs

Homebrew:
```rust
let path_include = "/opt/homebrew/include/";
let path_lib = "/opt/homebrew/lib";
```

MacPorts:
```rust
let path_include = "/opt/local/include";
let path_lib = "/opt/local/lib";
```

### 5 Step
Paste in your `src/main.rs`:
```rust
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]

mod bindings;
use bindings::*;

macro_rules! c_str {
    ($s:expr) => {
        concat!($s, "\0").as_ptr() as *const i8
    };
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn keyboard_game(key: SDL_Scancode, renderer: *mut renderer) {
    if key == SDL_Scancode_SDL_SCANCODE_E {
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn mouse_game(renderer: *mut renderer, x: i32, y: i32, button: u8) {
    
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn update_game(renderer: *mut renderer) {
    for i in 0..127 {
        draw_tile(renderer, i, BRIGHT_YELLOW.as_ptr(), (15 + (i % 16)) as i32, (i / 16) as i32);
    }

    print(renderer, c_str!("Hello World!"), BLUE.as_ptr(), 0, 0);
    print(renderer, c_str!("Hello World!"), GREEN.as_ptr(), 0, 1);
    print(renderer, c_str!("Hello World!"), CYAN.as_ptr(), 0, 2);
    print(renderer, c_str!("Hello World!"), RED.as_ptr(), 0, 3);
    print(renderer, c_str!("Hello World!"), MAGENTA.as_ptr(), 0, 4);
    print(renderer, c_str!("Hello World!"), BROWN.as_ptr(), 0, 5);
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn shutdown_game() {}

fn main() {
    unsafe {
        let mut core = std::mem::zeroed::<renderer>();

        if init_renderer(&mut core, 0, 2, c_str!("MyGame")) != 0 {
            std::process::exit(1);
        }

        run_render(&mut core);
        shutdown_renderer(&mut core);
    }
}
```

## Running
Just run:
```bash
cargo run
```

You might see a lot of warnings during compilation,   
but don’t worry, that’s normal

Result:
![screenshot](https://github.com/Ztry8/ASCII-Engine/raw/main/assets/example.png)

Good luck with your project!
