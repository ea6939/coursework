function Xhat = synthesis_bank(B,filter_bank)

% load('filtersCMFB.mat');
load('filtersLOT.mat');

size_size = size(H);
Xhat = zeros(size_size(1),size_size(2) + length(B(1,:))-1);

size_size = size(B);
for n = 1:size_size(1)
    Xhat(n,:) = conv(B(n,:), G(n,:));
end
end

