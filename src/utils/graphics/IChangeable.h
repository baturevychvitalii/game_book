#ifndef __INTERFACE_ICHANGEABLE__
#define __INTERFACE_ICHANGEABLE__

class IChangeable
{
    private:
        // will also be notified about change
        IChangeable * parent;
        bool up_to_date;
        
        virtual void ApplyChange() = 0;
    public:
        IChangeable(IChangeable * parent)
            :   parent(parent), 
                up_to_date(false)
        {
        }

        virtual ~IChangeable() = default;

        void Commit()
        {
            if (!up_to_date)
			{
				ApplyChange();
				up_to_date = true;
			}
        }

        void NotifyChange()
        {
            up_to_date = false;
            if (parent != nullptr)
                parent->NotifyChange();
        }

        bool UpToDate() const
        {
            return up_to_date;
        }

        void SetParent(IChangeable * new_parent)
        {
            parent = new_parent;
        }

		bool HasParent() const
		{
			return parent != nullptr;
		}
};


#endif
