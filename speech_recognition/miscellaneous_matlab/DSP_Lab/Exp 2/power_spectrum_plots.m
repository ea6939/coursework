

clean = wavread('CleanSig.wav');
noisy = wavread('NoisySig.wav');
group1 = wavread('DSPLabG1.wav');

T = length(clean);
T1 = length(group1);
fs = 10000;

cleanf = fft(clean);
noisyf = fft(noisy);
group1f = fft(group1);

t = 1:length(cleanf);
t1 = 1:length(group1);
f = t*fs/(length(t));
f1 = t1*fs/(length(t1));

cleanpower = (1/(2*T))*cleanf.^2;
noisypower = (1/(2*T))*noisyf.^2;
group1power = (1/(2*T1))*group1f.^2;

subplot(3,1,1), plot(f, abs(cleanpower));
title('Clean Signal');
subplot(3,1,2), plot(f, abs(noisypower));
title('Noisy Signal');
subplot(3,1,3), plot(f1, abs(group1power));
title('Group 1');
