{ pkgs ?  import <nixpkgs> {}
, stdenv ? pkgs.stdenv
, lib ? pkgs.lib
} :

stdenv.mkDerivation {
  name = "udprelay";
  buildInputs = with pkgs; [ gnumake ];
  src = builtins.filterSource (path: type:
    !(lib.strings.hasSuffix path "Makefile") &&
    !(lib.strings.hasSuffix path ".c")) ./.;

  makeFlags=[ "PREFIX=$(out)" ];
}
