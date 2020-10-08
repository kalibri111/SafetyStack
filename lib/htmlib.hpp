#ifndef HTMLIB_LIBRARY_H
#define HTMLIB_LIBRARY_H

#include <stdio.h>
#include <string.h>

/*
 * defines to concat predicate and unique line number
 * */
#define __div_generic__(X) d##X
#define __unique_div__(X) __div_generic__(X)

#define __h_generic__(X) h##X
#define __unique_h__(X) __h_generic__(X)

#define __p_generic__(X) p##X
#define __unique_p__(X) __p_generic__(X)

#define __head__(file) Head hd(file);
#define __body__(file) Body bd(file);

/*
 * unique div and p objects
 * */
#define __div__(file, class_name, obj_name) Div obj_name(file, class_name);
#define __p__(file, class_name, obj_name)   P   obj_name((file), class_name);
#define __h__(file, class_name, obj_name)   H   obj_name((file), class_name);

/*
 * common idea write open tag in constructor
 * and close tag in destructor
 * */
class Tag{
protected:
    FILE* file_;
};

class Head: Tag {
public:
    Head(FILE* file) {
        fputs("<head>\n"
              "    <meta charset=\"UTF-8\">\n"
              "    <title>",
              file
              );
        file_ = file;
    }
    ~Head() {
        fputs("</title>\n"
              "</head>\n",
              file_
              );
    }
};

class Body: Tag{
public:
    Body(FILE* file) {
        file_ = file;
        fputs("<body>\n", file);
    }

    ~Body(){
        fputs("</body>", file_);
    }
};

class Div: Tag{
public:
    Div(FILE* file, const char* class_name) {
        file_ = file;
        fputs("<div class=", file_);
        fputs(class_name     , file_);
        fputs(">\n"        , file_);
    }
    ~Div() {
        fputs("</div>\n", file_);
    }
};

class P: Tag{
public:
    P(FILE* file, const char* class_name) {
        file_ = file;
        fputs("<p class=", file_);
        fputs(class_name   , file_);
        fputs(">"        , file_);
    }

    ~P() {
        fputs("</p>", file_);
    }
};

class H:Tag {
public:
    H(FILE* file, const char* class_name) {
        file_ = file;
        fputs("<h5 class=", file_);
        fputs(class_name   , file_);
        fputs(">"        , file_);
    }

    ~H() {
        fputs("</h5>", file_);
    }
};

void link_bootstrap(FILE* file) {
    fputs("<!DOCTYPE html>\n"
          "<html lang=\"en\">\n"
          "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css\" integrity=\"sha384-JcKb8q3iqJ61gNV9KGb8thSsNjpSL0n8PARn9HuZOnIxN0hoP+VmmDGMN5t9UJ0Z\" crossorigin=\"anonymous\">\n"
          "<link rel=\"stylesheet\" href=\"log.css\"/>\n",
          file);
}

#endif //HTMLIB_LIBRARY_H
