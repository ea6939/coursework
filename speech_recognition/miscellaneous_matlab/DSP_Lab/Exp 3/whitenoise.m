% white noise image matrix

gauss = randn(128, 128);
gauss = 20 * gauss;
gauss = gauss + 128;
for i = 1:128
    for j = 1:128
        gauss(i,j) = ceil(gauss(i,j));
        if (gauss(i,j) > 255)
            gauss(i,j) = 255;
        elseif gauss(i,j) < 0
            gauss(i,j) = 0;
        end
    end
end
imagesc(gauss);
%colormap(gray);