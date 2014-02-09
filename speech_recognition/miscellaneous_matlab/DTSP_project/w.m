% hamming window

function window = w(offset,T0,padding)

% we need to make sure that shifting the window doesn't clip the 
window = zeros(1,ceil(-offset+padding));
for i = 1:ceil(-offset+padding);
if (abs(i+offset) <= T0/2)
    window(i) = 0.54 + 0.46*cos(2*pi*(i+offset-.5)/T0);
else
    window(i) = 0;
end
end