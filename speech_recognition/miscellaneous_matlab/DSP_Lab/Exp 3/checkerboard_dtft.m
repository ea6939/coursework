image = imread('checkerboard.tiff');
image_padded = zeros(1000);
image_padded(1:128,1:128) = image;
a = fft2(image_padded); % use this for fft with more points
% a = fft2(image); % use this for standard fft
b = 128/a(1,1);
mesh(abs(a*b));
view([0 0]);
