-- client.lua
-- wills
local socket = require("socket")
 
LClient = {}
gresult=''
presult=''
function LClient:create(o)
    o = o or { host='127.0.0.1',port=8888,timeout=0.1}
    setmetatable(o, self)
    self.__index = self
    self.sock = socket.connect(o.host, o.port)
    --self.sock:settimeout(0)
    return o
end

function gethead(argc,bodylen)
    local argcs,bodylens
    if(argc>=10 and argc<=100)then
         argcs="0"..argc;
    end
    if(argc<10)then
         argcs="00"..argc;
    end
    if(argc>=100)then
         argcs=""..argc;
    end

    if(bodylen<10)then
         bodylens="0000"..bodylen;
    end
    if(bodylen>=10 and bodylen<=100)then
         bodylens="000"..bodylen;
    end
    if(bodylen>=100 and bodylen<=1000)then
         bodylens="00"..bodylen;
    end
    return argcs..bodylens
end

function LClient:put(key,value)

    local ck=#key;
    local cv=#value;
    local body="3#put"..ck.."#"..key..cv.."#"..value;
    local bodylen=#body
    local head=gethead(3,bodylen)
    presult=''
    assert(self.sock)
    if #key > 0 and #value > 0 then
        assert(self.sock:send(head..body))
        local recvt, sendt, status = socket.select({self.sock}, nil, self.timeout)
        while #recvt > 0 do
            local response, receive_status = self.sock:receive(#recvt)
            presult=presult..response
            recvt, sendt, status = socket.select({self.sock}, nil, self.timeout)
        end
    end
    return presult
end

function LClient:get(key)
    local ck=#key;
    local body="3#get"..ck.."#"..key;
    local bodylen=#body
    local head=gethead(2,bodylen)
    assert(self.sock)
    gresult=''
    if #key > 0  then
        assert(self.sock:send(head..body))
        local recvt, sendt, status = socket.select({self.sock}, nil, self.timeout)
        while #recvt > 0 do
            local response, receive_status = self.sock:receive(#recvt)
            gresult=gresult..response
            recvt, sendt, status = socket.select({self.sock}, nil, self.timeout)
        end
    end
    return gresult
end

--client=LClient:create()
--print(client:put("lual","luas"))
--print(client:get("lual"))
