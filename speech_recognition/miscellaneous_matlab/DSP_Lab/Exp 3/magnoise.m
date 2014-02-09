image = imread('claire.tiff');
clairefft = fft2(image);
totalmag = zeros(288,360);
mag_noise1 = randn(288,360);

mag_noise2 = flipud(mag_noise1);
mag_noise3 = fliplr(mag_noise2);
mag_noise4 = fliplr(mag_noise1);
newmag1 = cat(1,mag_noise1, mag_noise2);
newmag2 = cat(1,mag_noise4, mag_noise3);
totalmag = cat(2,newmag2, newmag1);

phase_claire = cast(angle(clairefft), 'double');
newfft = abs(totalmag).*exp(i*phase_claire);

newimage = ifft2(newfft);

imagesc(abs(newimage));
colormap(gray);