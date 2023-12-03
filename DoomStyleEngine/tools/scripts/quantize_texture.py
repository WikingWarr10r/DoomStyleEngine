from PIL import Image

img = Image.open(input("Texture Path: "))

img = img.quantize(colors=32, method=2, dither=Image.Dither.FLOYDSTEINBERG)
img = img.resize((img.size[0] // 3, img.size[1] // 3))
img.save(input("Output Path: "))