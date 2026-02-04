# Mixel

**TODOS**
- [x] parse csv file
- [x] View table
- [x] evaluate expression with precedence *eg:* `=a1+b1*c1-d1`
- [x] evaluate function *eg:* `=sum(a1:b1)`
- [ ] simple charts build and export
- [ ] [lock support RAII(Resource Acquisition is initialization) implementation](https://en.cppreference.com/w/cpp/language/raii.html)


> **NOTE:**
> The Factory method of defining function feature is added.
> I am new to this feature too, found in fabric minecraft modding.
> So, It makes it a personal project
> Some part is copied from `cppreference.com`

## User guide
- In `src/functions/` you can add your own class with your own class sytem
- The evaluation() is define in IFunction class which is abstract class

**ALL In ALL THE CORE SYSTEM IS BUILT WITH UNIT TESTING FACILITY**
**YOU CAN USE IT ON CREATIVE COMMONS BY 4.0 LEGAL TEXT**
