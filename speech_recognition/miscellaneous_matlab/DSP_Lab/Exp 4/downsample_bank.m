function Y = downsample_bank(A)

size_size = size(A);
size_size(2) = ceil(size_size(2)/size_size(1));
Y = zeros(size_size);

for n = 1:size_size(1)
    Y(n,:) = downsample(A(n,:),size_size(1));
end
end