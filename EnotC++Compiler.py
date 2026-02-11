import os
import subprocess as sb

def clear_console():
    os.system('cls' if os.name == 'nt' else 'clear')

def build_project():
    pj_name = input('Enter project name (for .exe) ~ ').strip()
    if not pj_name: pj_name = "app"
    
    src_dir = 'src'
    include_dir = 'include'
    build_dir = 'build'

    if not os.path.exists(src_dir):
        print(f"[!] Error: '{src_dir}' folder not found!")
        return None

    if not os.path.exists(build_dir):
        os.makedirs(build_dir)

    obj_files = []
    cpp_files = [f for f in os.listdir(src_dir) if f.endswith('.cpp')]
    
    if not cpp_files:
        print("[!] No .cpp files found in src/")
        return None
    for file in cpp_files:
        name = file.replace('.cpp', '')
        cpp_path = os.path.join(src_dir, file)
        obj_path = os.path.join(build_dir, name + '.obj')

        print(f'Compiling {file}...')
        res = sb.run(f'g++ -I {include_dir} -c {cpp_path} -o {obj_path}', shell=True)
        
        if res.returncode != 0:
            print(f"[!] Compilation failed for {file}")
            return None
        obj_files.append(obj_path)

    all_objs = ' '.join(obj_files)
    exe_path = os.path.join(build_dir, pj_name + '.exe')
    
    print(f'Linking {pj_name}.exe...')

    res = sb.run(f'g++ {all_objs} -o {exe_path} -static -static-libgcc -static-libstdc++ -lsetupapi -luuid -lwinmm -O2', shell=True)
    
    if res.returncode == 0:
        print('--- Build Successful ---')
        return exe_path
    else:
        print('[!] Linking failed')
        return None

def main():
    clear_console()
    print('#########################################################')
    print('############## C++ Compiler author ~ Enot ###############')
    print('#########################################################')

    script_dir = os.path.dirname(os.path.abspath(__file__))
    os.chdir(script_dir)

    while True:
        print(f"\nCurrent DIR: {os.getcwd()}")
        cmd = input('\nCommand (build, alone, cd, clear, exit) > ').strip().lower()

        if cmd == 'exit':
            break
        elif cmd == 'clear':
            clear_console()
        elif cmd == 'cd':
            new_path = input('Enter new path > ')
            if os.path.exists(new_path):
                os.chdir(new_path)
            else:
                print("[!] Path doesn't exist")
        elif cmd == 'alone':
            while True:
                sub_cmd = input('alone > ')
                if sub_cmd == 'exit': break
                sb.run(sub_cmd, shell=True)
        elif cmd == 'build':
            exe = build_project()
            if exe:
                run_it = input('Build done. Run it? (y/n) > ').lower()
                if run_it == 'y':
                    print("\n--- Program Output ---")
                    sb.run(f".\\{exe}", shell=True)
        else:
            print("[!] Unknown command. Use 'build' for pro-structure or 'alone' for manual.")

if __name__ == '__main__':
    main()