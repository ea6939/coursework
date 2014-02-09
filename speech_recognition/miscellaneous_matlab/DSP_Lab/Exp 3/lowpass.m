h = zeros(576,720);
w1 = 100;
w2 = 100;
%%
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
        corrupted(m,n) = mod((clean(m,n)+ gauss(m,n)), 255);
    end
end

for n1 = 1: 576
    for n2 = 1:720
        G = 100000; % we were getting small values, so use large gain G
        h(n1, n2) =(G/(4*pi^2))*sinc(w1*n1/pi).*sinc(w2*n2/pi);
    end
end

% filter the noisy image using h

result = conv2(double(corrupted),h);

%%
for n1 = 1: 576
    for n2 = 1:720
        h(n1, n2) = result(n1, n2);
    end
end
%%
imagesc(255-abs(h));
colormap(gray);