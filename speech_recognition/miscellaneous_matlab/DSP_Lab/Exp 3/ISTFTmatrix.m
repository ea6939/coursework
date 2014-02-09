
function BLAM = ISTFTmatrix(A, size_subblock)
 
% BUT INVERSE

% get dimensions of matrix to be split into subblocks
dims = size(A);
num_rows = dims(1);
num_cols = dims(2);


% find number of rows of subblocks
num_subrows = floor(num_rows/size_subblock);
row_vector = size_subblock*ones(num_subrows,1);

% find number of columns of subblocks
num_subcols = floor(num_cols/size_subblock);
col_vector = size_subblock*ones(num_subcols,1);

BLAM = cell(num_subrows, num_subcols);

C = zeros(num_subrows*size_subblock,num_subcols*size_subblock);
for q = 1:num_subcols*size_subblock
    for p = 1:num_subrows*size_subblock
        C(p,q) = A(p,q);
    end
end

% split matrix using mat2cell
B = mat2cell(C,row_vector,col_vector);

for m = 1:num_subcols
    for n = 1:num_subrows
        BLAM{n,m} = ifft2(B{n,m});
    end
end

BLAM = cell2mat(BLAM);

end
