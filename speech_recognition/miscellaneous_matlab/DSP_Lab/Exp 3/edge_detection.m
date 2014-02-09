image = cast(imread('claire.tiff'), 'double');

new_image = zeros(576,720);
threshold = 100;

vertical_sobel_filter = fspecial('sobel');
horizontal_sobel_filter = transpose(vertical_sobel_filter);

edges = conv2(image, horizontal_sobel_filter);%vertical_sobel_filter);

% for n1 = 1:1:576
%     for n2 = 1:1:720
%         if(edges(n1,n2) > threshold)
%             new_image(n1,n2) = 255;
%         else new_image(n1,n2) = 0;
%         end
%     end
% end

%make the edges matrix the right dimensions
new_edges = zeros(576,720);
for n1 = 1:1:576
    for n2 = 1:1:720
        new_edges(n1,n2) = edges(n1,n2);
    end
end

%normalize the new picture with the edges between 1 and 255 

% norm_edges = abs(floor(new_edges/(max(new_edges)-min(new_edges))))*255;

composite = (image + new_image);
imagesc(composite);
colormap(gray);