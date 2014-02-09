clean = imread('claire.tiff');
corrupted = zeros(576,720);
reconstruct = zeros(576,720);
T = 5; 

gauss = randn(576, 720);
gauss = 20 * gauss;
gauss = gauss + 128;
for p = 1:128
    for q = 1:128
        gauss(p,q) = ceil(gauss(p,q));
        if (gauss(p,q) > 255)
            gauss(p,q) = 255;
        elseif gauss(p,q) < 0
            gauss(p,q) = 0;
        end
    end
end

for m = 1:576
    for n = 1:720
        corrupted(m,n) = 255-mod((clean(m,n)+ gauss(m,n)), 255);
    end
end

% imagesc(corrupted);
gauss_f = fft2(gauss);
mesh(abs(gauss_f/(576*720)));
% imagesc(clean);
% colormap(gray);



%%
clean_f = fft2(clean);
gauss_f = fft2(gauss);
corrupted_f = fft2(corrupted);
clean_power = abs(clean_f).^2;
gauss_power = abs(gauss_f).^2;
corrupted_power = abs(corrupted_f).^2;

SNR = corrupted_power./gauss_power;


for r = 1:576
    for s = 1:720
        if SNR(r,s) < T
            reconstruct(r,s) = 0;
        else reconstruct(r,s) = corrupted_f(r,s);
        end
    end
end

image = ifft2(reconstruct);
% imagesc(255-image);
mesh(abs(SNR));
% colormap(gray);
view([0 0]);
 