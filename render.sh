#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <scenes/scene.cfg>" >&2
    exit 84
fi

scene_cfg="$1"
if [[ ! -f "$scene_cfg" ]]; then
    echo "error: scene file not found: $scene_cfg" >&2
    exit 84
fi

scene_name="$(basename "$scene_cfg" .cfg)"
ppm_out="output.ppm"
png_out="screenshots/${scene_name}.png"

./raytracer "$scene_cfg"

mkdir -p screenshots

if command -v magick >/dev/null 2>&1; then
    magick "$ppm_out" "$png_out"
elif command -v convert >/dev/null 2>&1; then
    convert "$ppm_out" "$png_out"
elif command -v ffmpeg >/dev/null 2>&1; then
    ffmpeg -loglevel error -y -i "$ppm_out" "$png_out"
else
    echo "error: need one converter installed: magick, convert, or ffmpeg" >&2
    exit 84
fi

echo "saved -> $png_out"
