local LogFile = nil;
local function Log(str)
    if not LogFile then
        LogFile = assert(io.open("log.txt", "w"));
    end
    LogFile:write(str .. "\n");
end

local function GetClippings()
    local filename = "My Clippings.txt";
    local f = assert(io.open(filename,"r"));

    local clip = {};
    for line in f:lines() do
        clip[#clip + 1] = line;
    end
    f:close();

    return clip;
end


local function ConvertTitle(title)
    if string.sub(title, 1, 1) == "?" then
        title = string.sub(title, 2);
    end
    return title;
end

local function GetPathFromStr(str)
    str = string.gsub(str, "/", ""); 
    return str;
end

local function IsSameHeader(a, b)
    local res = false;
    if string.sub(a, 1, #a) ==  string.sub(b, 1, #a) then
        res = true;
    end
    return res;
end

--title
local function ConvertClipToBook(clip)
    local title, context, des, idxM;
    local books = {};
    local curBooks;
    for idx = 1, #clip do
        idxM = idx % 5;

        if idxM == 1 then
            title = clip[idx]; 
            title = ConvertTitle(title);
            curBooks = books[title];
            if not curBooks then
                curBooks = {};
                books[title] = curBooks;
                books[#books + 1] = title;
                Log("[new book]: " .. title);
            end 
        elseif idxM == 2 then
            --
        elseif idxM == 3 then
            --
        elseif idxM == 4 then
            context = clip[idx]; 
            if context ~= "" then
                curBooks[#curBooks + 1] = context;

                Log("" .. #curBooks .. ": " .. context);
            end
        end
    end
    return books;
end

local function WriteClipBooks(books)
    local title, book, line, preLine;
    local file;
    local lineIdx;
    for idx = 1, #books do
        title = books[idx];
        book = books[title];

        Log("[new out]:" .. title);
        file = assert(io.open("out/" .. GetPathFromStr(title) .. ".txt", "w"));

        file:write(title .. "\n");
        file:write("====\n");

        lineIdx = 1;
        preLine = book[1];
        for idxL = 2, #book do
            line = book[idxL];

            Log("==item=" .. idxL .. line);

            --如果前一行与当前行不是记录的同一处，则将前一行输出
            if not IsSameHeader(preLine, line) then
                file:write(lineIdx .. ".\t" .. preLine .. "\n");
                lineIdx = lineIdx + 1;

                Log("===" .. idxL);
                Log("preLine: " .. preLine);
                Log("line: " .. line);
            else
                --print(idxL);
            end

            preLine = line;
        end
        if preLine then
            file:write(lineIdx .. ".\t" .. preLine .. "\n");
        end
        
    end
end

local function Main()
    Log("====start====");
    os.execute("mkdir out");

    local clip = GetClippings();
    local books = ConvertClipToBook(clip);
    WriteClipBooks(books);

    Log("====end====");
    LogFile:close();
end


Main();