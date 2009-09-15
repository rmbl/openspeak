include (FindGettext)

set (GETTEXT_PACKAGE openspeak)

# Search for all .po files and create .mo files
file (GLOB PO_FILES *.po)
gettext_create_translations (${GETTEXT_PACKAGE}.pot ALL ${PO_FILES})

# Add custom target to update .pot file and .po files
file (GLOB_RECURSE ALL_SRC_FILES ${CMAKE_SOURCE_DIR}/*.cpp)
add_custom_target(update_pot
        COMMAND xgettext --default-domain=${GETTEXT_PACKAGE}
            --directory=${CMAKE_SOURCE_DIR} --files-from=POTFILES.in
            --copyright-holder=openSpeak\ Team --msgid-bugs-address=${BUG_EMAIL}
            --package-name=${PACKAGE_NAME} --package-version=${PACKAGE_VERSION}
            --force-po --c++ --boost --from-code=utf8 -j -s --keyword=_
            --output=${GETTEXT_PACKAGE}.pot
        COMMAND msgmerge --update ${PO_FILES} ./${GETTEXT_PACKAGE}.pot
        DEPENDS ${GETTEXT_PACKAGE}.pot
        )
