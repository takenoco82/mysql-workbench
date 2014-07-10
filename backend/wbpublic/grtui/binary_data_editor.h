/* 
 * Copyright (c) 2010, 2012,Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#ifndef __BINARY_DATA_EDITOR_H__
#define __BINARY_DATA_EDITOR_H__

#include "wbpublic_public_interface.h"

#include "mforms/box.h"
#include "mforms/form.h"
#include "mforms/tabview.h"
#include "mforms/label.h"
#include "mforms/button.h"

namespace bec {
  class GRTManager;
};

class BinaryDataEditor;

class WBPUBLICBACKEND_PUBLIC_FUNC BinaryDataViewer : public mforms::Box
{
public:
  BinaryDataViewer(BinaryDataEditor *owner);

  virtual void data_changed() = 0;

protected:
  BinaryDataEditor *_owner;
};


class WBPUBLICBACKEND_PUBLIC_FUNC BinaryDataEditor : public mforms::Form
{
public:
  BinaryDataEditor(bec::GRTManager *grtm, const char *data, size_t length, bool read_only=true);
  BinaryDataEditor(bec::GRTManager *grtm, const char *data, size_t length, const std::string &text_encoding, bool read_only=true);
  virtual ~BinaryDataEditor();
  
  const char* data() const { return _data; }
  size_t length() const { return _length; }

  // when user clicks Save
  boost::signals2::signal<void ()> signal_saved;
  
public:
  void add_viewer(BinaryDataViewer *viewer, const std::string &title);

  void assign_data(const char *data, size_t length);
  void notify_edit();
  
  bool read_only() { return _read_only; }

protected:
  bec::GRTManager *_grtm;
  char *_data;
  size_t _length;

  // editor, needs-update
  std::vector<std::pair<BinaryDataViewer*, bool> > _viewers;

  mforms::Box _box;
  mforms::Box _hbox;
  mforms::TabView _tab_view;
  mforms::Label _length_text;
  mforms::Button _save;
  mforms::Button _close;
  mforms::Button _export;
  mforms::Button _import;
  
  bool _read_only;
  
  void setup();
  void save();
  void tab_changed();
  
  void import_value();
  void export_value();
};


#endif /* __BINARY_DATA_EDITOR_H__ */