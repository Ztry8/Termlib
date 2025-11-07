# Build your Rust-game on Termlib

## Installation
Install all necessary tools and libs as written in this [section](https://github.com/Ztry8/Termlib/tree/main?tab=readme-ov-file#building-for-cc)   
Additionaly you need [rustc and cargo](https://rust-lang.org/learn/get-started/)

## Setting up your environment 

### 1 Step
Firstly just create new project:
```
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
cc = "*"
bindgen = "*"
```

### 3 Step
Create `native` folder and paste [`library.h`](https://github.com/Ztry8/Termlib/blob/main/src/core.h) there,   
Create `main.c` inside `native` folder and paste in it this content:
```c
#include "core.h"
```
(Yes, only one line of code in this file)

### 4 Step
Create `build.rs` in your project root and paste this code: 
```rust
fn main() {
    let path_include = "/opt/local/include";
    let path_lib = "/opt/local/lib";

    cc::Build::new()
        .file("native/core.c")
        .include("native")
        .include(path_include)
        //.define("SHOW_FPS", None)
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
}

```
#### Please pay attention that you need to set up your library path

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
pub unsafe extern "C" fn input_game(key: SDL_Scancode, renderer: *mut renderer) {
    if key == SDL_Scancode_SDL_SCANCODE_E {
    }
}


#[unsafe(no_mangle)]
pub unsafe extern "C" fn update_game(renderer: *mut renderer) {
    for i in 0..127 {
        draw_tile(renderer, i, BRIGHT_YELLOW.as_ptr(), (15 + (i % 16)) as i64, (i / 16) as i64);
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

### 6 Step
Just run:
```bash
cargo run
```
You will see many warnings but don't worry it's normal

Result:
![screensht](https://github.com/Ztry8/ASCII-Engine/raw/main/assets/example.png)
