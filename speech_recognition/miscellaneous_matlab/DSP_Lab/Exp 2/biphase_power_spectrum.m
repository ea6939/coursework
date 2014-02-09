

% Plot of Gs(f) = (2/T) * |Sh(f)|^2 (1 - cos(3pifT))

T = 0.01;  % pulse width
fs = 10000; % sampling frequency
f = 1:fs;
 
high = ones(10, 1);       % make a pulse and take the fft
low = zeros(9990, 1);
rectangle = cat(1, high, low)';
S = fft(rectangle);

G = (2/T)*abs(S).^2.*(1-cos(3*pi*f*T));

figure(1);
subplot(2,1,1), plot(abs(S));
title('Frequency response of the signal');
subplot(2,1,2), plot(G);
title('Power spectrum of the signal');
axis([0 5000 0 50000]);