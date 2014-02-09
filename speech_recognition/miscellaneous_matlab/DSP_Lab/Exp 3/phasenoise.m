image = imread('claire.tiff');
clairefft = fft2(image);
totalphase = zeros(288,360);
phase_noise1 = randn(288,360);

phase_noise2 = -flipud(phase_noise1);
phase_noise3 = -fliplr(phase_noise2);
phase_noise4 = -fliplr(phase_noise1);
newphase1 = cat(1,phase_noise1, phase_noise2);
newphase2 = cat(1,phase_noise4, phase_noise3);
totalphase = (1/5)*cat(2,newphase2, newphase1);


for m = 1:576
    for n = 1:720
        %phase_noise(i,j) = ceil(phase_noise(i,j));
        if (totalphase(m,n) > pi)
            totalphase(m,n) = pi;
        elseif totalphase(m,n) < 0
            totalphase(m,n) = -pi;
        end
    end
end


real_claire = cast(real(clairefft), 'double');
newfft = real_claire.*exp(i*totalphase);

newimage = ifft2(newfft);

imagesc(abs(newimage));
colormap(gray);