local tasks = {}
local option = arg[1]

local function run(cmd)
    print("> "..cmd)
    local success, exit_type, code = os.execute(cmd)

    if not success then
        error(string.format(
            "Command failed (%s, code %d): %s",
            exit_type or "unknown",
            code or -1,
            cmd
        ))
    end
end

tasks["configure"] = function()
    run('cmake -S . -B build')
end

tasks["build"] = function()
    run('cmake --build build')
end

tasks["run"] = function()
    run('./build/src/virtel')
end

tasks["test"] = function()
    run('ctest --output-on-failure --test-dir build')
end

tasks["clean"] = function()
    run("rm -rf build")
end

if not option or option == '' then
    print('Usage: lua ./scripts/build.lua [option]')
    print('Available tasks:')
    for name in pairs(tasks) do
        print(" - "..name)
    end
    os.exit(1)
end

if tasks[option] then
    tasks[option]()
else
    error("Unknown task: "..option)
end
