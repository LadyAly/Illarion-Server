#   illarionserver - server for the game Illarion
#   Copyright 2011 Illarion e.V.
#
#   This file is part of illarionserver.
#
#   illarionserver is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   illarionserver is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#
#   You should have received a copy of the GNU Affero General Public License
#   along with illarionserver.  If not, see <http://www.gnu.org/licenses/>.


AUTOMAKE_OPTIONS = foreign 
ACLOCAL_AMFLAGS = -Im4

SUBDIRS = src test

EXTRA_DIST = $(GTEST_DIR)/include \
             $(GTEST_DIR)/src \
             $(GMOCK_DIR)/include \
             $(GMOCK_DIR)/src

dist_sysconf_DATA=setup/illarion.conf

clean-local:
	-rm -rf $(top_builddir)/src/version.hpp $(top_builddir)/test/data
