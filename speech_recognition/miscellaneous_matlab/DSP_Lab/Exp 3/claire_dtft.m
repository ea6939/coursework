clear
image = imread('claire.tiff');
a = fft2(image);
b = 0.000061273;
mesh(abs(a*b)) %lower frequencies
view([0 0]);
