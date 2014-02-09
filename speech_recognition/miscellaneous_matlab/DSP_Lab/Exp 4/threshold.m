function result = threshold(a,b)

epsilon = 0.0002;
if (abs(a - b) < epsilon) 
    result = 1;
else
    result = 0;
end

end