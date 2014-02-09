function Hd = iirBLAM
%IIRBLAM Returns a discrete-time filter object.

%
% MATLAB Code
% Generated by MATLAB(R) 7.14 and the Signal Processing Toolbox 6.17.
%
% Generated on: 16-Feb-2013 21:18:41
%

% Butterworth Lowpass filter designed using FDESIGN.LOWPASS.

% All frequency values are in Hz.
Fs = 10000;  % Sampling Frequency

Fpass = 1250;        % Passband Frequency
Fstop = 1450;        % Stopband Frequency
Apass = 1;           % Passband Ripple (dB)
Astop = 80;          % Stopband Attenuation (dB)
match = 'passband';  % Band to match exactly

% Construct an FDESIGN object and call its BUTTER method.
h  = fdesign.lowpass(Fpass, Fstop, Apass, Astop, Fs);
Hd = design(h, 'butter', 'MatchExactly', match);

% [EOF]