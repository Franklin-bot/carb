# Milan and Franklin's money printing machine

### 1. Install Conan and Set Up Profile
### 2. Install Dependencies
```
conan install . --output-folder=build --build=missing
```
### 3. Build
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release && cmake --build .
```
