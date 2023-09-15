// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: task.proto

#ifndef PROTOBUF_task_2eproto__INCLUDED
#define PROTOBUF_task_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace KPS {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_task_2eproto();
void protobuf_AssignDesc_task_2eproto();
void protobuf_ShutdownFile_task_2eproto();

class mp_task_data;
class mp_task;

// ===================================================================

class mp_task_data : public ::google::protobuf::Message {
 public:
  mp_task_data();
  virtual ~mp_task_data();
  
  mp_task_data(const mp_task_data& from);
  
  inline mp_task_data& operator=(const mp_task_data& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const mp_task_data& default_instance();
  
  void Swap(mp_task_data* other);
  
  // implements Message ----------------------------------------------
  
  mp_task_data* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const mp_task_data& from);
  void MergeFrom(const mp_task_data& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 task_index = 1;
  inline bool has_task_index() const;
  inline void clear_task_index();
  static const int kTaskIndexFieldNumber = 1;
  inline ::google::protobuf::uint32 task_index() const;
  inline void set_task_index(::google::protobuf::uint32 value);
  
  // required string project_name = 2;
  inline bool has_project_name() const;
  inline void clear_project_name();
  static const int kProjectNameFieldNumber = 2;
  inline const ::std::string& project_name() const;
  inline void set_project_name(const ::std::string& value);
  inline void set_project_name(const char* value);
  inline void set_project_name(const char* value, size_t size);
  inline ::std::string* mutable_project_name();
  
  // required string path_name = 3;
  inline bool has_path_name() const;
  inline void clear_path_name();
  static const int kPathNameFieldNumber = 3;
  inline const ::std::string& path_name() const;
  inline void set_path_name(const ::std::string& value);
  inline void set_path_name(const char* value);
  inline void set_path_name(const char* value, size_t size);
  inline ::std::string* mutable_path_name();
  
  // @@protoc_insertion_point(class_scope:KPS.mp_task_data)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint32 task_index_;
  ::std::string* project_name_;
  static const ::std::string _default_project_name_;
  ::std::string* path_name_;
  static const ::std::string _default_path_name_;
  friend void  protobuf_AddDesc_task_2eproto();
  friend void protobuf_AssignDesc_task_2eproto();
  friend void protobuf_ShutdownFile_task_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static mp_task_data* default_instance_;
};
// -------------------------------------------------------------------

class mp_task : public ::google::protobuf::Message {
 public:
  mp_task();
  virtual ~mp_task();
  
  mp_task(const mp_task& from);
  
  inline mp_task& operator=(const mp_task& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const mp_task& default_instance();
  
  void Swap(mp_task* other);
  
  // implements Message ----------------------------------------------
  
  mp_task* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const mp_task& from);
  void MergeFrom(const mp_task& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 task_id = 1;
  inline bool has_task_id() const;
  inline void clear_task_id();
  static const int kTaskIdFieldNumber = 1;
  inline ::google::protobuf::uint32 task_id() const;
  inline void set_task_id(::google::protobuf::uint32 value);
  
  // required string task_name = 2;
  inline bool has_task_name() const;
  inline void clear_task_name();
  static const int kTaskNameFieldNumber = 2;
  inline const ::std::string& task_name() const;
  inline void set_task_name(const ::std::string& value);
  inline void set_task_name(const char* value);
  inline void set_task_name(const char* value, size_t size);
  inline ::std::string* mutable_task_name();
  
  // required string ontime_do = 3;
  inline bool has_ontime_do() const;
  inline void clear_ontime_do();
  static const int kOntimeDoFieldNumber = 3;
  inline const ::std::string& ontime_do() const;
  inline void set_ontime_do(const ::std::string& value);
  inline void set_ontime_do(const char* value);
  inline void set_ontime_do(const char* value, size_t size);
  inline ::std::string* mutable_ontime_do();
  
  // repeated .KPS.mp_task_data data = 4;
  inline int data_size() const;
  inline void clear_data();
  static const int kDataFieldNumber = 4;
  inline const ::KPS::mp_task_data& data(int index) const;
  inline ::KPS::mp_task_data* mutable_data(int index);
  inline ::KPS::mp_task_data* add_data();
  inline const ::google::protobuf::RepeatedPtrField< ::KPS::mp_task_data >&
      data() const;
  inline ::google::protobuf::RepeatedPtrField< ::KPS::mp_task_data >*
      mutable_data();
  
  // @@protoc_insertion_point(class_scope:KPS.mp_task)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint32 task_id_;
  ::std::string* task_name_;
  static const ::std::string _default_task_name_;
  ::std::string* ontime_do_;
  static const ::std::string _default_ontime_do_;
  ::google::protobuf::RepeatedPtrField< ::KPS::mp_task_data > data_;
  friend void  protobuf_AddDesc_task_2eproto();
  friend void protobuf_AssignDesc_task_2eproto();
  friend void protobuf_ShutdownFile_task_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static mp_task* default_instance_;
};
// ===================================================================


// ===================================================================

// mp_task_data

// required uint32 task_index = 1;
inline bool mp_task_data::has_task_index() const {
  return _has_bit(0);
}
inline void mp_task_data::clear_task_index() {
  task_index_ = 0u;
  _clear_bit(0);
}
inline ::google::protobuf::uint32 mp_task_data::task_index() const {
  return task_index_;
}
inline void mp_task_data::set_task_index(::google::protobuf::uint32 value) {
  _set_bit(0);
  task_index_ = value;
}

// required string project_name = 2;
inline bool mp_task_data::has_project_name() const {
  return _has_bit(1);
}
inline void mp_task_data::clear_project_name() {
  if (project_name_ != &_default_project_name_) {
    project_name_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& mp_task_data::project_name() const {
  return *project_name_;
}
inline void mp_task_data::set_project_name(const ::std::string& value) {
  _set_bit(1);
  if (project_name_ == &_default_project_name_) {
    project_name_ = new ::std::string;
  }
  project_name_->assign(value);
}
inline void mp_task_data::set_project_name(const char* value) {
  _set_bit(1);
  if (project_name_ == &_default_project_name_) {
    project_name_ = new ::std::string;
  }
  project_name_->assign(value);
}
inline void mp_task_data::set_project_name(const char* value, size_t size) {
  _set_bit(1);
  if (project_name_ == &_default_project_name_) {
    project_name_ = new ::std::string;
  }
  project_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_task_data::mutable_project_name() {
  _set_bit(1);
  if (project_name_ == &_default_project_name_) {
    project_name_ = new ::std::string;
  }
  return project_name_;
}

// required string path_name = 3;
inline bool mp_task_data::has_path_name() const {
  return _has_bit(2);
}
inline void mp_task_data::clear_path_name() {
  if (path_name_ != &_default_path_name_) {
    path_name_->clear();
  }
  _clear_bit(2);
}
inline const ::std::string& mp_task_data::path_name() const {
  return *path_name_;
}
inline void mp_task_data::set_path_name(const ::std::string& value) {
  _set_bit(2);
  if (path_name_ == &_default_path_name_) {
    path_name_ = new ::std::string;
  }
  path_name_->assign(value);
}
inline void mp_task_data::set_path_name(const char* value) {
  _set_bit(2);
  if (path_name_ == &_default_path_name_) {
    path_name_ = new ::std::string;
  }
  path_name_->assign(value);
}
inline void mp_task_data::set_path_name(const char* value, size_t size) {
  _set_bit(2);
  if (path_name_ == &_default_path_name_) {
    path_name_ = new ::std::string;
  }
  path_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_task_data::mutable_path_name() {
  _set_bit(2);
  if (path_name_ == &_default_path_name_) {
    path_name_ = new ::std::string;
  }
  return path_name_;
}

// -------------------------------------------------------------------

// mp_task

// required uint32 task_id = 1;
inline bool mp_task::has_task_id() const {
  return _has_bit(0);
}
inline void mp_task::clear_task_id() {
  task_id_ = 0u;
  _clear_bit(0);
}
inline ::google::protobuf::uint32 mp_task::task_id() const {
  return task_id_;
}
inline void mp_task::set_task_id(::google::protobuf::uint32 value) {
  _set_bit(0);
  task_id_ = value;
}

// required string task_name = 2;
inline bool mp_task::has_task_name() const {
  return _has_bit(1);
}
inline void mp_task::clear_task_name() {
  if (task_name_ != &_default_task_name_) {
    task_name_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& mp_task::task_name() const {
  return *task_name_;
}
inline void mp_task::set_task_name(const ::std::string& value) {
  _set_bit(1);
  if (task_name_ == &_default_task_name_) {
    task_name_ = new ::std::string;
  }
  task_name_->assign(value);
}
inline void mp_task::set_task_name(const char* value) {
  _set_bit(1);
  if (task_name_ == &_default_task_name_) {
    task_name_ = new ::std::string;
  }
  task_name_->assign(value);
}
inline void mp_task::set_task_name(const char* value, size_t size) {
  _set_bit(1);
  if (task_name_ == &_default_task_name_) {
    task_name_ = new ::std::string;
  }
  task_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_task::mutable_task_name() {
  _set_bit(1);
  if (task_name_ == &_default_task_name_) {
    task_name_ = new ::std::string;
  }
  return task_name_;
}

// required string ontime_do = 3;
inline bool mp_task::has_ontime_do() const {
  return _has_bit(2);
}
inline void mp_task::clear_ontime_do() {
  if (ontime_do_ != &_default_ontime_do_) {
    ontime_do_->clear();
  }
  _clear_bit(2);
}
inline const ::std::string& mp_task::ontime_do() const {
  return *ontime_do_;
}
inline void mp_task::set_ontime_do(const ::std::string& value) {
  _set_bit(2);
  if (ontime_do_ == &_default_ontime_do_) {
    ontime_do_ = new ::std::string;
  }
  ontime_do_->assign(value);
}
inline void mp_task::set_ontime_do(const char* value) {
  _set_bit(2);
  if (ontime_do_ == &_default_ontime_do_) {
    ontime_do_ = new ::std::string;
  }
  ontime_do_->assign(value);
}
inline void mp_task::set_ontime_do(const char* value, size_t size) {
  _set_bit(2);
  if (ontime_do_ == &_default_ontime_do_) {
    ontime_do_ = new ::std::string;
  }
  ontime_do_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_task::mutable_ontime_do() {
  _set_bit(2);
  if (ontime_do_ == &_default_ontime_do_) {
    ontime_do_ = new ::std::string;
  }
  return ontime_do_;
}

// repeated .KPS.mp_task_data data = 4;
inline int mp_task::data_size() const {
  return data_.size();
}
inline void mp_task::clear_data() {
  data_.Clear();
}
inline const ::KPS::mp_task_data& mp_task::data(int index) const {
  return data_.Get(index);
}
inline ::KPS::mp_task_data* mp_task::mutable_data(int index) {
  return data_.Mutable(index);
}
inline ::KPS::mp_task_data* mp_task::add_data() {
  return data_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::KPS::mp_task_data >&
mp_task::data() const {
  return data_;
}
inline ::google::protobuf::RepeatedPtrField< ::KPS::mp_task_data >*
mp_task::mutable_data() {
  return &data_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_task_2eproto__INCLUDED
