# wlib-memory

Memory creation and destruction for WLib. Unlike `wlib-malloc` which
allocates raw memory, `create` and `destroy` will call constructors
and destructors.

### Usage
Constructor arguments can be passed to `create`,

```c++
UserDescription *user = create<UserDescription>("John", "Smith", 25);
char *characters = create<char[]>(64);
int *integer = create<int>(15);
// ...
destroy(user); // implicit type deduction
destroy<char[]>(characters);
destroy<int>(integer);

```
