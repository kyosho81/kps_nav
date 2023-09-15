// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pallet_cargo.proto

#ifndef PROTOBUF_pallet_5fcargo_2eproto__INCLUDED
#define PROTOBUF_pallet_5fcargo_2eproto__INCLUDED

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
void  protobuf_AddDesc_pallet_5fcargo_2eproto();
void protobuf_AssignDesc_pallet_5fcargo_2eproto();
void protobuf_ShutdownFile_pallet_5fcargo_2eproto();

class mp_pallet_cargo;

// ===================================================================

class mp_pallet_cargo : public ::google::protobuf::Message {
 public:
  mp_pallet_cargo();
  virtual ~mp_pallet_cargo();
  
  mp_pallet_cargo(const mp_pallet_cargo& from);
  
  inline mp_pallet_cargo& operator=(const mp_pallet_cargo& from) {
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
  static const mp_pallet_cargo& default_instance();
  
  void Swap(mp_pallet_cargo* other);
  
  // implements Message ----------------------------------------------
  
  mp_pallet_cargo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const mp_pallet_cargo& from);
  void MergeFrom(const mp_pallet_cargo& from);
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
  
  // required bool auto_create_pallet = 1;
  inline bool has_auto_create_pallet() const;
  inline void clear_auto_create_pallet();
  static const int kAutoCreatePalletFieldNumber = 1;
  inline bool auto_create_pallet() const;
  inline void set_auto_create_pallet(bool value);
  
  // required bool auto_destruct_pallet = 2;
  inline bool has_auto_destruct_pallet() const;
  inline void clear_auto_destruct_pallet();
  static const int kAutoDestructPalletFieldNumber = 2;
  inline bool auto_destruct_pallet() const;
  inline void set_auto_destruct_pallet(bool value);
  
  // required string pallet_type_uuid = 3;
  inline bool has_pallet_type_uuid() const;
  inline void clear_pallet_type_uuid();
  static const int kPalletTypeUuidFieldNumber = 3;
  inline const ::std::string& pallet_type_uuid() const;
  inline void set_pallet_type_uuid(const ::std::string& value);
  inline void set_pallet_type_uuid(const char* value);
  inline void set_pallet_type_uuid(const char* value, size_t size);
  inline ::std::string* mutable_pallet_type_uuid();
  
  // required string cargo_type_uuid = 4;
  inline bool has_cargo_type_uuid() const;
  inline void clear_cargo_type_uuid();
  static const int kCargoTypeUuidFieldNumber = 4;
  inline const ::std::string& cargo_type_uuid() const;
  inline void set_cargo_type_uuid(const ::std::string& value);
  inline void set_cargo_type_uuid(const char* value);
  inline void set_cargo_type_uuid(const char* value, size_t size);
  inline ::std::string* mutable_cargo_type_uuid();
  
  // required uint32 ms_produce_time = 5;
  inline bool has_ms_produce_time() const;
  inline void clear_ms_produce_time();
  static const int kMsProduceTimeFieldNumber = 5;
  inline ::google::protobuf::uint32 ms_produce_time() const;
  inline void set_ms_produce_time(::google::protobuf::uint32 value);
  
  // required uint32 ms_consume_time = 6;
  inline bool has_ms_consume_time() const;
  inline void clear_ms_consume_time();
  static const int kMsConsumeTimeFieldNumber = 6;
  inline ::google::protobuf::uint32 ms_consume_time() const;
  inline void set_ms_consume_time(::google::protobuf::uint32 value);
  
  // required uint32 full_size = 7;
  inline bool has_full_size() const;
  inline void clear_full_size();
  static const int kFullSizeFieldNumber = 7;
  inline ::google::protobuf::uint32 full_size() const;
  inline void set_full_size(::google::protobuf::uint32 value);
  
  // required uint32 current_size = 8;
  inline bool has_current_size() const;
  inline void clear_current_size();
  static const int kCurrentSizeFieldNumber = 8;
  inline ::google::protobuf::uint32 current_size() const;
  inline void set_current_size(::google::protobuf::uint32 value);
  
  // repeated string cargo_uuid = 9;
  inline int cargo_uuid_size() const;
  inline void clear_cargo_uuid();
  static const int kCargoUuidFieldNumber = 9;
  inline const ::std::string& cargo_uuid(int index) const;
  inline ::std::string* mutable_cargo_uuid(int index);
  inline void set_cargo_uuid(int index, const ::std::string& value);
  inline void set_cargo_uuid(int index, const char* value);
  inline void set_cargo_uuid(int index, const char* value, size_t size);
  inline ::std::string* add_cargo_uuid();
  inline void add_cargo_uuid(const ::std::string& value);
  inline void add_cargo_uuid(const char* value);
  inline void add_cargo_uuid(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& cargo_uuid() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_cargo_uuid();
  
  // required string operation_list = 10;
  inline bool has_operation_list() const;
  inline void clear_operation_list();
  static const int kOperationListFieldNumber = 10;
  inline const ::std::string& operation_list() const;
  inline void set_operation_list(const ::std::string& value);
  inline void set_operation_list(const char* value);
  inline void set_operation_list(const char* value, size_t size);
  inline ::std::string* mutable_operation_list();
  
  // @@protoc_insertion_point(class_scope:KPS.mp_pallet_cargo)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  bool auto_create_pallet_;
  bool auto_destruct_pallet_;
  ::std::string* pallet_type_uuid_;
  static const ::std::string _default_pallet_type_uuid_;
  ::std::string* cargo_type_uuid_;
  static const ::std::string _default_cargo_type_uuid_;
  ::google::protobuf::uint32 ms_produce_time_;
  ::google::protobuf::uint32 ms_consume_time_;
  ::google::protobuf::uint32 full_size_;
  ::google::protobuf::uint32 current_size_;
  ::google::protobuf::RepeatedPtrField< ::std::string> cargo_uuid_;
  ::std::string* operation_list_;
  static const ::std::string _default_operation_list_;
  friend void  protobuf_AddDesc_pallet_5fcargo_2eproto();
  friend void protobuf_AssignDesc_pallet_5fcargo_2eproto();
  friend void protobuf_ShutdownFile_pallet_5fcargo_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(10 + 31) / 32];
  
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
  static mp_pallet_cargo* default_instance_;
};
// ===================================================================


// ===================================================================

// mp_pallet_cargo

// required bool auto_create_pallet = 1;
inline bool mp_pallet_cargo::has_auto_create_pallet() const {
  return _has_bit(0);
}
inline void mp_pallet_cargo::clear_auto_create_pallet() {
  auto_create_pallet_ = false;
  _clear_bit(0);
}
inline bool mp_pallet_cargo::auto_create_pallet() const {
  return auto_create_pallet_;
}
inline void mp_pallet_cargo::set_auto_create_pallet(bool value) {
  _set_bit(0);
  auto_create_pallet_ = value;
}

// required bool auto_destruct_pallet = 2;
inline bool mp_pallet_cargo::has_auto_destruct_pallet() const {
  return _has_bit(1);
}
inline void mp_pallet_cargo::clear_auto_destruct_pallet() {
  auto_destruct_pallet_ = false;
  _clear_bit(1);
}
inline bool mp_pallet_cargo::auto_destruct_pallet() const {
  return auto_destruct_pallet_;
}
inline void mp_pallet_cargo::set_auto_destruct_pallet(bool value) {
  _set_bit(1);
  auto_destruct_pallet_ = value;
}

// required string pallet_type_uuid = 3;
inline bool mp_pallet_cargo::has_pallet_type_uuid() const {
  return _has_bit(2);
}
inline void mp_pallet_cargo::clear_pallet_type_uuid() {
  if (pallet_type_uuid_ != &_default_pallet_type_uuid_) {
    pallet_type_uuid_->clear();
  }
  _clear_bit(2);
}
inline const ::std::string& mp_pallet_cargo::pallet_type_uuid() const {
  return *pallet_type_uuid_;
}
inline void mp_pallet_cargo::set_pallet_type_uuid(const ::std::string& value) {
  _set_bit(2);
  if (pallet_type_uuid_ == &_default_pallet_type_uuid_) {
    pallet_type_uuid_ = new ::std::string;
  }
  pallet_type_uuid_->assign(value);
}
inline void mp_pallet_cargo::set_pallet_type_uuid(const char* value) {
  _set_bit(2);
  if (pallet_type_uuid_ == &_default_pallet_type_uuid_) {
    pallet_type_uuid_ = new ::std::string;
  }
  pallet_type_uuid_->assign(value);
}
inline void mp_pallet_cargo::set_pallet_type_uuid(const char* value, size_t size) {
  _set_bit(2);
  if (pallet_type_uuid_ == &_default_pallet_type_uuid_) {
    pallet_type_uuid_ = new ::std::string;
  }
  pallet_type_uuid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_cargo::mutable_pallet_type_uuid() {
  _set_bit(2);
  if (pallet_type_uuid_ == &_default_pallet_type_uuid_) {
    pallet_type_uuid_ = new ::std::string;
  }
  return pallet_type_uuid_;
}

// required string cargo_type_uuid = 4;
inline bool mp_pallet_cargo::has_cargo_type_uuid() const {
  return _has_bit(3);
}
inline void mp_pallet_cargo::clear_cargo_type_uuid() {
  if (cargo_type_uuid_ != &_default_cargo_type_uuid_) {
    cargo_type_uuid_->clear();
  }
  _clear_bit(3);
}
inline const ::std::string& mp_pallet_cargo::cargo_type_uuid() const {
  return *cargo_type_uuid_;
}
inline void mp_pallet_cargo::set_cargo_type_uuid(const ::std::string& value) {
  _set_bit(3);
  if (cargo_type_uuid_ == &_default_cargo_type_uuid_) {
    cargo_type_uuid_ = new ::std::string;
  }
  cargo_type_uuid_->assign(value);
}
inline void mp_pallet_cargo::set_cargo_type_uuid(const char* value) {
  _set_bit(3);
  if (cargo_type_uuid_ == &_default_cargo_type_uuid_) {
    cargo_type_uuid_ = new ::std::string;
  }
  cargo_type_uuid_->assign(value);
}
inline void mp_pallet_cargo::set_cargo_type_uuid(const char* value, size_t size) {
  _set_bit(3);
  if (cargo_type_uuid_ == &_default_cargo_type_uuid_) {
    cargo_type_uuid_ = new ::std::string;
  }
  cargo_type_uuid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_cargo::mutable_cargo_type_uuid() {
  _set_bit(3);
  if (cargo_type_uuid_ == &_default_cargo_type_uuid_) {
    cargo_type_uuid_ = new ::std::string;
  }
  return cargo_type_uuid_;
}

// required uint32 ms_produce_time = 5;
inline bool mp_pallet_cargo::has_ms_produce_time() const {
  return _has_bit(4);
}
inline void mp_pallet_cargo::clear_ms_produce_time() {
  ms_produce_time_ = 0u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 mp_pallet_cargo::ms_produce_time() const {
  return ms_produce_time_;
}
inline void mp_pallet_cargo::set_ms_produce_time(::google::protobuf::uint32 value) {
  _set_bit(4);
  ms_produce_time_ = value;
}

// required uint32 ms_consume_time = 6;
inline bool mp_pallet_cargo::has_ms_consume_time() const {
  return _has_bit(5);
}
inline void mp_pallet_cargo::clear_ms_consume_time() {
  ms_consume_time_ = 0u;
  _clear_bit(5);
}
inline ::google::protobuf::uint32 mp_pallet_cargo::ms_consume_time() const {
  return ms_consume_time_;
}
inline void mp_pallet_cargo::set_ms_consume_time(::google::protobuf::uint32 value) {
  _set_bit(5);
  ms_consume_time_ = value;
}

// required uint32 full_size = 7;
inline bool mp_pallet_cargo::has_full_size() const {
  return _has_bit(6);
}
inline void mp_pallet_cargo::clear_full_size() {
  full_size_ = 0u;
  _clear_bit(6);
}
inline ::google::protobuf::uint32 mp_pallet_cargo::full_size() const {
  return full_size_;
}
inline void mp_pallet_cargo::set_full_size(::google::protobuf::uint32 value) {
  _set_bit(6);
  full_size_ = value;
}

// required uint32 current_size = 8;
inline bool mp_pallet_cargo::has_current_size() const {
  return _has_bit(7);
}
inline void mp_pallet_cargo::clear_current_size() {
  current_size_ = 0u;
  _clear_bit(7);
}
inline ::google::protobuf::uint32 mp_pallet_cargo::current_size() const {
  return current_size_;
}
inline void mp_pallet_cargo::set_current_size(::google::protobuf::uint32 value) {
  _set_bit(7);
  current_size_ = value;
}

// repeated string cargo_uuid = 9;
inline int mp_pallet_cargo::cargo_uuid_size() const {
  return cargo_uuid_.size();
}
inline void mp_pallet_cargo::clear_cargo_uuid() {
  cargo_uuid_.Clear();
}
inline const ::std::string& mp_pallet_cargo::cargo_uuid(int index) const {
  return cargo_uuid_.Get(index);
}
inline ::std::string* mp_pallet_cargo::mutable_cargo_uuid(int index) {
  return cargo_uuid_.Mutable(index);
}
inline void mp_pallet_cargo::set_cargo_uuid(int index, const ::std::string& value) {
  cargo_uuid_.Mutable(index)->assign(value);
}
inline void mp_pallet_cargo::set_cargo_uuid(int index, const char* value) {
  cargo_uuid_.Mutable(index)->assign(value);
}
inline void mp_pallet_cargo::set_cargo_uuid(int index, const char* value, size_t size) {
  cargo_uuid_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_cargo::add_cargo_uuid() {
  return cargo_uuid_.Add();
}
inline void mp_pallet_cargo::add_cargo_uuid(const ::std::string& value) {
  cargo_uuid_.Add()->assign(value);
}
inline void mp_pallet_cargo::add_cargo_uuid(const char* value) {
  cargo_uuid_.Add()->assign(value);
}
inline void mp_pallet_cargo::add_cargo_uuid(const char* value, size_t size) {
  cargo_uuid_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
mp_pallet_cargo::cargo_uuid() const {
  return cargo_uuid_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
mp_pallet_cargo::mutable_cargo_uuid() {
  return &cargo_uuid_;
}

// required string operation_list = 10;
inline bool mp_pallet_cargo::has_operation_list() const {
  return _has_bit(9);
}
inline void mp_pallet_cargo::clear_operation_list() {
  if (operation_list_ != &_default_operation_list_) {
    operation_list_->clear();
  }
  _clear_bit(9);
}
inline const ::std::string& mp_pallet_cargo::operation_list() const {
  return *operation_list_;
}
inline void mp_pallet_cargo::set_operation_list(const ::std::string& value) {
  _set_bit(9);
  if (operation_list_ == &_default_operation_list_) {
    operation_list_ = new ::std::string;
  }
  operation_list_->assign(value);
}
inline void mp_pallet_cargo::set_operation_list(const char* value) {
  _set_bit(9);
  if (operation_list_ == &_default_operation_list_) {
    operation_list_ = new ::std::string;
  }
  operation_list_->assign(value);
}
inline void mp_pallet_cargo::set_operation_list(const char* value, size_t size) {
  _set_bit(9);
  if (operation_list_ == &_default_operation_list_) {
    operation_list_ = new ::std::string;
  }
  operation_list_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_cargo::mutable_operation_list() {
  _set_bit(9);
  if (operation_list_ == &_default_operation_list_) {
    operation_list_ = new ::std::string;
  }
  return operation_list_;
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

#endif  // PROTOBUF_pallet_5fcargo_2eproto__INCLUDED