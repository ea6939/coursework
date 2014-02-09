image = imread('claire.tiff');
y = zeros(576,720);
T = 110;


for n1 = 1:1:576
    for n2 = 1:1:720
        if(image(n1,n2) > T)
            y(n1,n2) = 1;
        else y(n1,n2) = 0;
        end
    end
end

imagesc(y);
colormap(gray);