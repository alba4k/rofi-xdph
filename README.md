# rofi-xdph

Use [Rofi](https://github.com/davatorium/rofi) as a graphical frontend for [xdg-desktop-portal](https://github.com/hyprwm/xdg-desktop-portal-hyprland)'s share picker.

<img width="480" height="300" alt="immagine" src="https://github.com/user-attachments/assets/bd3b7f20-079f-4c54-9480-757f591b586c" />

Used a lot of code from [hyprland-share-picker](https://github.com/hyprwm/xdg-desktop-portal-hyprland/blob/master/hyprland-share-picker).

## Usage

All you need to do to use this after installing it is add the following to your `~/.config/hypr/xdph.conf`
```
screencopy:custom_picker_binary = rofi-xdph
```

If you have `screencopy:allow_token_by_default = true`, it will work with `rofi-xdph` too (although there is no way to change that toggle on-the-fly).
