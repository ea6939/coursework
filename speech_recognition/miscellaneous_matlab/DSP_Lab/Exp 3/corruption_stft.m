clean = imread('claire.tiff');
corrupted = zeros(576,720);
reconstruct = zeros(576,720);
T = 5; 

% vary T and STFT size to get different qualities

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
        corrupted(m,n) = mod((clean(m,n)+ gauss(m,n)), 255);
    end
end



%%
clean_f = STFTmatrix(clean,16);
gauss_f = STFTmatrix(gauss,16);
corrupted_f = STFTmatrix(corrupted,16);
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

image = ISTFTmatrix(reconstruct,16);
imagesc(255-image);
% mesh(SNR);
% view([0 0]);
colormap(gray);