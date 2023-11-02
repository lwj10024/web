#include "lsDxf.h"

#include <string.h>
#include <stdlib.h>

// init the lsDxf structure and open the DXF file
bool ls_dxf_init(lsDxf *dxf, const char *filepath)
{
    memset(dxf->stringLine, '\0', sizeof(dxf->stringLine));

    dxf->fp = fopen(filepath, "r");
    if (!dxf->fp)
    {
        printf("DXF file load failed\n");
        return false;
    }

    return true;
}

// read a line string from the dxf file stream
bool ls_dxf_get_line(lsDxf *dxf)
{
    if (NULL == fgets(dxf->stringLine, sizeof(dxf->stringLine), dxf->fp))
        return false;

    char tmp[1024];
    size_t len = strlen(dxf->stringLine);

    int j = 0;
    bool non_whitespace_found = false;

    // 1. trim the ' ' and '\t' at the begining of the string
    // 2. ignore the return character in the string
    for (size_t i = 0; i < len; ++i)
    {
        char c = dxf->stringLine[i];
        if (non_whitespace_found || (' ' != c && '\t' != c))
        {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            if ('\r' != c && '\n' != c)
                tmp[j++] = c;

            non_whitespace_found = true;
#else
            if ('\r' != c)
                tmp[j++] = c;

            non_whitespace_found = true;
#endif
        }
    }

    tmp[j] = 0;
    strcpy(dxf->stringLine, tmp);
    return true;
}

// read the entity::line form the dxf file
bool ls_dxf_read_entity_line(lsDxf *dxf)
{
    lsPoint s = {0, 0, 0};
    lsPoint e = {0, 0, 0};

    while (!feof(dxf->fp))
    {
        ls_dxf_get_line(dxf);

        // try to read a number
        int n;
        if (1 != sscanf(dxf->stringLine, "%d", &n))
        {
            printf("ls_dxf_read_entity_line failed to read integer from '%s'\n", dxf->stringLine);
            return false;
        }

        // recognize the group code
        switch (n)
        {
        case 0:
            // now, we get a group '0', finish read line
            lsLine line;
            line.s = s;
            line.e = e;
            dxf->entitys.push_back(ls_entity_convert_line(&line));
            return true;

        case 10:
            // start point x
            ls_dxf_get_line(dxf);
            s.x = strtod(dxf->stringLine, NULL);
            break;

        case 20:
            // start point y
            ls_dxf_get_line(dxf);
            s.y = strtod(dxf->stringLine, NULL);
            break;

        case 30:
            // start point z
            ls_dxf_get_line(dxf);
            s.z = strtod(dxf->stringLine, NULL);
            break;

        case 11:
            // end point x
            ls_dxf_get_line(dxf);
            e.x = strtod(dxf->stringLine, NULL);
            break;

        case 21:
            // end point y
            ls_dxf_get_line(dxf);
            e.y = strtod(dxf->stringLine, NULL);
            break;

        case 31:
            // end point z
            ls_dxf_get_line(dxf);
            e.z = strtod(dxf->stringLine, NULL);
            break;

        default:
            ls_dxf_get_line(dxf);// skip next line
            break;
        }
    }

    // should be return in the 'case 0'
    return false;
}

// read the entity::circle form the dxf file
bool ls_dxf_read_entity_circle(lsDxf *dxf)
{
    lsReal radius = 0.0;
    lsPoint center = {0.0, 0.0, 0.0};

    while (!feof(dxf->fp))
    {
        ls_dxf_get_line(dxf);

        // try to read a number
        int n;
        if (1 != sscanf(dxf->stringLine, "%d", &n))
        {
            printf("ls_dxf_read_entity_circle failed to read integer from '%s'\n", dxf->stringLine);
            return false;
        }

        // recognize the group code
        switch (n)
        {
        case 0:
            // now, we get a group '0', finish read circle
            lsCircle circle;
            circle.c = center;
            circle.r = radius;
            dxf->entitys.push_back(ls_entity_convert_circle(&circle));
            return true;

        case 10:
            // center x
            ls_dxf_get_line(dxf);
            center.x = strtod(dxf->stringLine, NULL);
            break;

        case 20:
            // center y
            ls_dxf_get_line(dxf);
            center.y = strtod(dxf->stringLine, NULL);
            break;

        case 30:
            // center z
            ls_dxf_get_line(dxf);
            center.z = strtod(dxf->stringLine, NULL);
            break;

        case 40:
            // radius
            ls_dxf_get_line(dxf);
            radius = strtod(dxf->stringLine, NULL);
            break;

        default:
            ls_dxf_get_line(dxf);// skip next line
            break;
        }
    }

    // should be return in the 'case 0'
    return false;
}

// read the entity::arc form the dxf file
bool ls_dxf_read_entity_arc(lsDxf* dxf)
{
    lsReal stangle = 0.0;
    lsReal endangle = 0.0;
    lsPoint lup= { 0.0, 0.0, 0.0 };
    lsPoint rlow = { 0.0, 0.0, 0.0 };

    while (!feof(dxf->fp))
    {
        ls_dxf_get_line(dxf);

        // try to read a number
        int n;
        if (1 != sscanf(dxf->stringLine, "%d", &n))
        {
            printf("ls_dxf_read_entity_arc failed to read integer from '%s'\n", dxf->stringLine);
            return false;
        }

        // recognize the group code
        switch (n)
        {
        case 0:
            // now, we get a group '0', finish read arc
            lsArc arc;
            arc.lup = lup;
            arc.rlow = rlow;
            arc.stangle = stangle;
            arc.endangle = endangle;
            dxf->entitys.push_back(ls_entity_convert_arc(&arc));
            return true;

        case 10:
            // lup x
            ls_dxf_get_line(dxf);
            lup.x = strtod(dxf->stringLine, NULL);
            break;

        case 20:
            // center y
            ls_dxf_get_line(dxf);
           lup.y = strtod(dxf->stringLine, NULL);
            break;

        case 30:
            // center z
            ls_dxf_get_line(dxf);
            lup.z = strtod(dxf->stringLine, NULL);
            break;

        case 40:
            // rlow x
            ls_dxf_get_line(dxf);
            rlow.x= strtod(dxf->stringLine, NULL);
            break;

        case 50:
            // rlow y
            ls_dxf_get_line(dxf);
            rlow.y = strtod(dxf->stringLine, NULL);
            break;

        case 60:
            // rlow z
            ls_dxf_get_line(dxf);
            rlow.z = strtod(dxf->stringLine, NULL);
            break;

        case 70:
            // stangle 
            ls_dxf_get_line(dxf);
            stangle= strtod(dxf->stringLine, NULL);
            break;

        case 80:
            // endangle
            ls_dxf_get_line(dxf);
            endangle= strtod(dxf->stringLine, NULL);
            break;

        default:
            ls_dxf_get_line(dxf);// skip next line
            break;
        }
    }

    // should be return in the 'case 0'
    return false;
}

// parse DXF file
void ls_dxf_parse(lsDxf *dxf)
{
    if (!ls_dxf_get_line(dxf))
        return;

    while (!feof(dxf->fp))
    {
        // group code '0' indicating the entity type
        if (!strcmp("0", dxf->stringLine))
        {
            ls_dxf_get_line(dxf);

            // indicating the entity::line
            if (!strcmp("LINE", dxf->stringLine))
            {
                if (!ls_dxf_read_entity_line(dxf))
                {
                    printf("ls_dxf_do_read failed to read line\n");
                    return;
                }

                // move on to the next group code '0' we got
                continue;
            }

            else if (!strcmp("CIRCLE", dxf->stringLine))
            {
                if (!ls_dxf_read_entity_circle(dxf))
                {
                    printf("ls_dxf_do_read failed to read circle\n");
                    return;
                }

                // move on to the next group code '0' we got
                continue;
            }

            else if (!strcmp("ARC", dxf->stringLine))
            {
                if (!ls_dxf_read_entity_arc(dxf))
                {
                    printf("ls_dxf_do_read failed to read arc\n");
                    return;
                }

                // move on to the next group code '0' we got
                continue;
            }
        }

        // read next line
        ls_dxf_get_line(dxf);
    }
}

// show the entity information after the DXF has been parsed
void ls_dxf_result_print(lsDxf *dxf)
{
    for (size_t i = 0; i < dxf->entitys.size(); ++i)
    {
        const lsEntity *ent = &dxf->entitys[i];

        switch (ent->type)
        {
        case kLine:
            printf("Entity::Line [s(%.3f, %.3f) - e(%.3f, %.3f)]\n",
                ent->data.line.s.x, ent->data.line.s.y, ent->data.line.e.x, ent->data.line.e.y);
            break;

        case kCircle:
            printf("Entity::Circle [c(%.3f, %.3f) - r(%.3f)]\n",
                ent->data.circle.c.x, ent->data.circle.c.y, ent->data.circle.r);
            break;

        case kArc:
            printf("Entity::Arc [lup(%.3f, %.3f) - rlow(%.3f, %.3f)- stangle(%.3f)-endangle(%.3f)]\n",
                ent->data.arc.lup.x, ent->data.arc.lup.y, ent->data.arc.rlow.x, ent->data.arc.rlow.y, ent->data.arc.stangle, ent->data.arc.endangle);
            break;
        }
    }
}
