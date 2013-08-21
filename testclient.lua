-- client.lua
local socket = require("socket")
dofile('client.lua')

function Split(szFullString, szSeparator)
local nFindStartIndex = 1
local nSplitIndex = 1
local nSplitArray = {}
while true do
   local nFindLastIndex = string.find(szFullString, szSeparator, nFindStartIndex)
   if not nFindLastIndex then
    nSplitArray[nSplitIndex] = string.sub(szFullString, nFindStartIndex, string.len(szFullString))
    break
   end
   nSplitArray[nSplitIndex] = string.sub(szFullString, nFindStartIndex, nFindLastIndex - 1)
   nFindStartIndex = nFindLastIndex + string.len(szSeparator)
   nSplitIndex = nSplitIndex + 1
end
return nSplitArray
end

local client=LClient:create()
index=0
while true do
	io.write("levedb"..index..">")
    input = io.read()
    if input == 'exit' or input == 'quit' then
        break
    end
    if #input > 0 and input ~='\n' then
        ss=Split(input,' ');
        if(ss[1]=="get")then
            print(client:get(ss[2]))
        elseif(ss[1]=="put")then
            print(client:put(ss[2],ss[3]))
        end
        index=index+1 
    end
      
end


