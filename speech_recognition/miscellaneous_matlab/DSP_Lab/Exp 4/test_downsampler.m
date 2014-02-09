size_size = size(A);
size_size(2) = floor(size_size(2)/32);
Y = zeros(size_size);

for n = 1:32
    Y(n,:) = downsample(A(n,:),32);
end
