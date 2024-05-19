{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.SDL2
    pkgs.SDL2_gfx  # Using SDL2_gfx instead of SDL2_ttf
    pkgs.pkg-config
    pkgs.makeWrapper
  ];

  shellHook = ''
    export SDL2_LIBS="-L${pkgs.SDL2}/lib -lSDL2"
    export SDL2_CFLAGS="-I${pkgs.SDL2}/include/SDL2"
    export SDL2_GFX_LIBS="-L${pkgs.SDL2_gfx}/lib -lSDL2_gfx"
    export SDL2_GFX_CFLAGS="-I${pkgs.SDL2_gfx}/include/SDL2"
  '';
}