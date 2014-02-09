function A = analysis_bank(x,filter_bank)

% load('filtersCMFB.mat');
load(filter_bank);
size_size=size(H);

% A = zeros(32,256 + length(x)-1);
A = zeros(size_size(1),size_size(2) + length(x)-1);

size_size = size(A);
number_of_filters = size_size(1);

for n = 1:number_of_filters
    A(n,:) = conv(x, H(n,:));
end
end

