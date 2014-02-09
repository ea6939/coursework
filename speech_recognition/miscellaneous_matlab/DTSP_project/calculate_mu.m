% calculate mu
function m = calculate_mu(B,last_window_index)

% m is a frequency spectrum (specifically, the average of all the frequency
% spectra before the silence ends)

spectral_sum = 0*(B(1,:));

for i = 1:last_window_index-1
    spectral_sum = spectral_sum + abs(B(i,:));
end

m = spectral_sum/last_window_index;

end