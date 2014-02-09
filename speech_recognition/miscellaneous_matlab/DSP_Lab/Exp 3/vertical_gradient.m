%ECSE 490 Final Demo Isabel Helleur April 3, 2013

image = cast(imread('claire.tiff'), 'double');

new_image = zeros(576,720);%create a new matrix for the new image

threshold = 100; %define a threshold for edge detection

vertical_sobel_filter = fspecial('sobel');

%convolve the image with the Sobel filter
edges = conv2(image, vertical_sobel_filter);

%use a thresholding scheme to find the edges
for n1 = 1:1:576
    for n2 = 1:1:720
        if(edges(n1,n2) > threshold)
            new_image(n1,n2) = 255; %above threshold -> max value
        else new_image(n1,n2) = 0; %below threshold -> min value
        end
    end
end

%add the image with the defined edges to the original image
composite = (image + new_image);
imagesc(composite);
colormap(gray);